#include <iostream>
#include "tcp/io_service.h"
#include "http/http.h"

using namespace std;

#define DEFAULT_PORT 8030

int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    try
    {
        if (argc == 2) {
            port = atoi(argv[1]);
        } else if (argc > 2) {
            cerr << "Usage: LiveChat <port>\n";
            return 1;
        }

        cout << "LiveChat started on port " << port << endl;

        IO_Service::io_service_ptr io(new IO_Service());
        Server::server_ptr server(new Server(io, port));

        Http::http_ptr http(new Http());

        http->set_static_root("static/");

        io->set_http([http](Http::buffer_ptr buffer)->void{
            http->resolve(Request::request_ptr(new Request(buffer)));
        });

        http->get("/users/add", [](Request::request_ptr req, Response::response_ptr res)->void{
            res->add_header("Connection: keep-alive");
            res->add_header("Cache-Control: no-cache,no-store,max-age=0,must-revalidate");

            std::string data = "{\"route\":\"123456789\"}";
            res->set_data(data);
        });

        http->get("/", [http](Request::request_ptr req, Response::response_ptr res)->void{
            res->set_content_type("text/html");
            res->set_data(http->get_static_file("index.html"));
        });
        http->get("/js/jquery.js", [http](Request::request_ptr req, Response::response_ptr res)->void{
            res->set_content_type("text/plain");
            res->set_data(http->get_static_file("js/jquery.js"));
        });
        http->get("/js/scripts.js", [http](Request::request_ptr req, Response::response_ptr res)->void{
            res->set_content_type("text/html");
            res->set_data(http->get_static_file("js/scripts.js"));
        });


        io->start();
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
