#include <iostream>
#include "io_service.h"
#include "socket.h"
#include "../debug/debug.h"
#include "signaler.h"

/* CONSTRUCTORS & DESTRUCTOR */

IO_Service::IO_Service() {
    printf(" [io_service]\n");

    epfd = epoll_create(MAX_EVENTS_COUNT);
    if (epfd == -1) {
        log_error("Failed to create epoll", FATAL_ERROR);
    }
    Signaler::register_service(IO_Service::io_service_ptr(this));
    signal(SIGINT, Signaler::signal_int);
    signal(SIGABRT, Signaler::signal_abrt);
}
IO_Service::~IO_Service() {
    printf("~[io_service]\n");

    sockets.clear();

    if (epfd != -1) {
        close(epfd);
    }
}

/* PUBLIC FUNCTIONS */

int IO_Service::start() {
    this->running = true;
    while(this->running) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS_COUNT, -1);
        for (int i = 0; i < nfds; ++i) {
            Socket::socket_ptr socket = get_socket_by_fd(events[i].data.fd);
            if (!socket) {
                printf("socket with such fd not found\n");
                continue;
            }
            if (events[i].data.fd == server->_socket->fd) {
                //printf("event in server fd\n");
                if (server->accept1(socket) == -1) {
                    stop();
                }
            } else {


                if (events[i].events == EPOLLIN) {
                    printf("EPOLLIN event in %d fd\n", socket->fd);
                    //std::shared_ptr<std::string> ptr(new std::string());
                    socket->read_some([this, socket](const int& code, const int bytes_transferred)->void{
                        std::cout << "read bytes = " << bytes_transferred << std::endl;
                        std::cout << "read str = " << (*socket->buffer) << std::endl;

                        http(socket->buffer);
                    });
                } else if (events[i].events == EPOLLOUT) {
                    printf("EPOLLOUT event in %d fd\n", socket->fd);
                    socket->write_some([socket](const int& code, const int bytes_transferred)->void{
                        std::cout << "write bytes = " << bytes_transferred << std::endl;
                        std::cout << "write str = " << (*socket->buffer) << std::endl;
                    });
                }
            }
        }
    }
    return 0;
}

void IO_Service::stop() {
    this->running = false;
}

int IO_Service::add_socket(Socket::socket_ptr socket) {
    //printf("add_socket fd = %d\n", socket->fd);
    this->fd_to_socket[socket->fd] = (int)this->sockets.size();
    this->sockets.push_back(socket);

    epoll_event event;
    event.data.fd = socket->fd;
    event.events = EPOLLIN;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, socket->fd, &event) < 0) {
        log_error("Failed to add_socket()", ERROR_MESSAGE);
        return -1;
    }
    return 0;
}

int IO_Service::set_server(server_ptr server) {
    this->server = server;
    return 0;
}

int IO_Service::set_http(std::function<void(buffer_ptr)> http) {
    this->http = http;
    return 0;
}

/* PRIVATE FUNCTIONS */

Socket::socket_ptr IO_Service::get_socket_by_fd(const int& fd) {
    //printf("fd=%d\n", fd);
    if (fd_to_socket.find(fd) != fd_to_socket.end()) {
        //printf("index = %d\n", fd_to_socket[fd]);
        return sockets[fd_to_socket[fd]];
    }
    return nullptr;
}