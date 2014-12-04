#include "ioloop.h"
#include "handler.h"
#include "server.h"
#include "client.h"
#include "debug.h"

Server::Server(Server* other) : Handler(other->fd, other->addr) {}
Server::Server(int port) {
    this->fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->fd == -1) {
        log_error("Failed to create handler socket", FATAL_ERROR);
    }
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->addr.sin_port = htons(port);
    if (bind(this->fd, (sockaddr*)&(this->addr), sizeof(this->addr)) == -1) {
        log_error("Failed to bind handler socket", FATAL_ERROR);
    }
    if (listen(this->fd, MAX_PENDING) == -1) {
        log_error("Failed to listen on handler socket", FATAL_ERROR);
    }
    this->set_nonblocking();
    IOLoop::Instance()->add_handler(fd, this, EPOLLIN);
    printf("Server started (fd = %d)\n", fd);
}
Server::~Server() {
    printf("Server:destructor\n");
}

int Server::handle(epoll_event event) {
    log_epoll_event(event);

    sockaddr_in client_addr;
    socklen_t ca_len = sizeof(client_addr);
    int client_fd = accept(fd, (sockaddr*)&client_addr, &ca_len);

    if (client_fd == -1) {
        log_error("Error accepting", ERROR_MESSAGE);
        return -1;
    }

    Client* client = new Client(client_fd, client_addr);
    IOLoop::Instance()->add_handler(client_fd, client, EPOLLIN);
    onConnected(client);

    return 0;
}

void Server::onConnected(Client* client) {}
