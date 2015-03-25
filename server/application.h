//
// Created by creed on 22.03.15.
//

#ifndef _HTTPSERVER_APPLICATION_H_
#define _HTTPSERVER_APPLICATION_H_

#include "headers.h"
#include "tcp/io_service.h"
#include "http/http.h"

struct Application {
public:
    typedef std::shared_ptr<Application> application_ptr;
    typedef std::function<void(Http::http_ptr)> Handler;
    Application(int port);
    void on_start(Handler handler);
    void start();
    void stop();
    void set_root_dir(const std::string dir);
    void set_static_dir(const std::string dir);
private:
    int port;
    IO_Service::io_service_ptr io;
    Server::server_ptr server;
    Http::http_ptr http;
};

#endif //_HTTPSERVER_APPLICATION_H_
