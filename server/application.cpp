//
// Created by creed on 22.03.15.
//
#include "application.h"

using namespace std;

Application::Application(int port) : port(port) {
    try {
        io = IO_Service::io_service_ptr(new IO_Service());
        server = Server::server_ptr(new Server(io, port));
        http = Http::http_ptr(new Http());

        io->set_http([this](Http::buffer_ptr buffer)->void{
            http->resolve(Request::request_ptr(new Request(buffer)));
        });
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    cout << "HttpServer started on port " << port << endl;
}

void Application::start() {
    try {
        io->start();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

}

void Application::stop() {
    io->stop();
}

void Application::on_start(Handler handler) {
    try {
        handler(http);
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}

void Application::set_root_dir(const std::string dir) {
    http->set_root_dir(dir);
}

void Application::set_static_dir(const std::string dir) {
    http->set_static_dir(dir);
}
