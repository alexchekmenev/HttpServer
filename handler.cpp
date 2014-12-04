#include "handler.h"

Handler::Handler() : fd(), addr() {}
Handler::Handler(int fd, sockaddr_in addr) : fd(fd), addr(addr) {}
Handler::~Handler() {
    printf("Handler:destructor: fd = %d\n", fd);
    close(fd);
}

int Handler::set_nonblocking() {
    int flags = 0;
    if ((flags = fcntl(this->fd, F_GETFL, 0)) == -1) {
        flags = 0;
    }
    return fcntl(this->fd, F_SETFL, flags | O_NONBLOCK);
}

int Handler::handle(epoll_event e) { return -1; }
