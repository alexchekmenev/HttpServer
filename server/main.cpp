#include <iostream>
#include "application.h"
#include "model/chat.h"

using namespace std;

#define DEFAULT_PORT 8030

int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    if (argc == 2) {
        port = atoi(argv[1]);
    } else if (argc > 2) {
        cerr << "Usage: HttpServer <port>\n";
        return 1;
    }

    Application::application_ptr app(new Application(port));
    app->set_root_dir("../");
    app->set_static_dir("public/app/");

    shared_ptr<Chat> chat(new Chat());

    app->on_start([&](Http::http_ptr http)->void{

        /* index files */
        http->redirect("/", "index.html");

        /* Users endpoints */
        http->post("/users/add/", [&](Request::request_ptr req, Response::response_ptr res)->void{
            User user(req->get_parameter("name"));
            int id = chat->add_user(user);
            string data;
            if (id == -1) {
                data = "{\"error\":\"User already exists\"}";
            } else {
                data = "{\"token\":\""+chat->get_token(user)+"\",\"id\":\""+std::to_string(id)+"\"}";
            }
            res->write(data);
        });
        http->get("/users/me/", [&](Request::request_ptr req, Response::response_ptr res)->void{
            string token = req->get_parameter("token"), data;
            int user_id = chat->get_user_id_by_token(token);
            if (user_id == 0) {
                data = "{\"error\":\"Wrong token\"}";
            } else {
                string name = chat->get_user_by_id(user_id).get_name();
                data = "{\"user\":{\"name\":\""+name+"\"}}";
            }
            res->write(data);
        });
        http->get("/users/", [&](Request::request_ptr req, Response::response_ptr res)->void{
            string token = req->get_parameter("token"), data;
            int user_id = chat->get_user_id_by_token(token);
            if (user_id != 0) {
                vector<User> users = chat->get_users();
                data = "[]";
                for(int i = 0; i < (int)users.size(); i++) {
                    data.insert(data.size() - 1, (string)(i>0?",":"")+users[i].to_json());
                }
                data = "{\"users\":"+data+"}";
            } else {
                data = "{\"error\":\"Wrong token\"}";
            }
            res->write(data);
        });

        /* Messages endpoints */
        http->post("/messages/add/", [&](Request::request_ptr req, Response::response_ptr res)->void{
            string token = req->get_parameter("token"), data;
            int user_id = chat->get_user_id_by_token(token);
            if (user_id != 0) {
                User user = chat->get_user_by_id(user_id);
                Message message(user.get_name(), req->get_parameter("data"));
                chat->add_message(message);
                data = "{}";
            } else {
                data = "{\"error\":\"Wrong token\"}";
            }
            res->write(data);
        });

        http->get("/messages/", [&](Request::request_ptr req, Response::response_ptr res)->void{
            string token = req->get_parameter("token"), data;
            int user_id = chat->get_user_id_by_token(token);
            if (user_id != 0) {
                vector <Message> messages = chat->get_messages();
                data = "[]";
                for(int i = 0; i < (int)messages.size(); i++) {
                    data.insert(data.size() - 1, (string)(i>0?",":"")+messages[i].to_json());
                }
                data = "{\"messages\":"+data+"}";
            } else {
                data = "{\"error\":\"Wrong token\"}";
            }
            res->write(data);
        });
    });

    app->start();

    return 0;
}
