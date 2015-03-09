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

        //auto self(std::__enable_shared_from_this);
        io->set_http([http](Http::buffer_ptr buffer)->void{
            printf("resolver start epfd = %d\n", http->);
            http->resolve(Request::request_ptr(new Request(buffer)));
        });

        http->get("/", [](Request::request_ptr req, Response::response_ptr res)->void{
            res->add_header("Server: nginx");
            res->add_header("Connection: keep-alive");
            res->add_header("Keep-Alive: timeout=10");
            res->add_header("Cache-Control: no-cache,no-store,max-age=0,must-revalidate");

            std::string data = "{\"test\":\"test\"}";
            res->set_data(data);

            printf("[RESPONSE]:  %s\n", res->to_buffer()->c_str());
        });

        io->start();
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
