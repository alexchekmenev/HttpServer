#include "ioloop.h"
#include "handler.h"
#include "client.h"
#include "debug.h"

Client::Client(int fd, sockaddr_in addr) : Handler(fd, addr) {
    this->buffer = new char[BUFFER_SIZE];
    this->received = 0;
}
Client::Client(Client* other) : Handler(other->fd, other->addr) {
    this->buffer = new char[BUFFER_SIZE];
    this->received = 0;
}
Client::~Client() {
    printf("Client:destructor\n");
}

int Client::handle(epoll_event e) {
    log_epoll_event(e);
    if(e.events & EPOLLHUP) {
        IOLoop::Instance()->remove_handler(fd);
        return -1;
    }
    if(e.events & EPOLLERR) {
        return -1;
    }
    if (e.events & EPOLLOUT) {
        if (received > 0) {
            //buffer = "sdfsdfsdf\n";
            //received = strlen(buffer);
            printf("Writing %d bytes: %s\n", received, buffer);
            if (send(fd, buffer, received, 0) != received) {
                log_error("Could not write to stream", ERROR_MESSAGE);
                return -1;
            }
        }
        received = 0;
        IOLoop::Instance()->update_handler(fd, EPOLLIN);
        return 0;
    }
    if(e.events & EPOLLIN) {
        if ((received = recv(fd, buffer, BUFFER_SIZE, 0)) == -1) {
            log_error("Error reading from socket", ERROR_MESSAGE);
            return -1;
        } else {
            buffer[received] = 0;
            printf("Reading %d bytes: %s\n", received, buffer);
        }

        if(received > 0) {
            IOLoop::Instance()->update_handler(fd, EPOLLOUT);
        } else {
            IOLoop::Instance()->remove_handler(fd);
        }
        return 0;
    }

}
