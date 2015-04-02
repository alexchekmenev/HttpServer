#include "application.h"

using namespace std;

Application::Application(int port) : port(port) {
    io = IO_Service::io_service_ptr(new IO_Service());
    server = Server::server_ptr(new Server(io, port));
    http = Http::http_ptr(new Http());

    io->set_buffer_handler([this](Http::buffer_ptr buffer) -> void {
        http->resolve(Request::request_ptr(new Request(buffer)));
    });
    cout << "HttpServer started on port " << port << endl;
}

Application::~Application() {
    cout << "io.count = " << io.use_count() << endl;
    cout << "server.count = " << server.use_count() << endl;
    cout << "http.count = " << http.use_count() << endl;
    io->stop();
}

void Application::start() {
    io->start();
}

void Application::stop() {
    io->stop();
}

void Application::on_start(Handler handler) {
    handler(http);
}

void Application::set_root_dir(const std::string dir) {
    http->set_root_dir(dir);
}

void Application::set_static_dir(const std::string dir) {
    http->set_static_dir(dir);
}

