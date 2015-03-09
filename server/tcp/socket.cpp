#include "socket.h"
#include "../debug/debug.h"

/* CONSTRUCTORS & DESTRUCTOR */

Socket::Socket(io_service_ptr _io, const int& fd, const sockaddr_in& addr) : io(_io), fd(fd), addr(addr) {
    printf(" [socket]: fd = %d\n", fd);
    buffer = buffer_ptr(new std::string());
}
Socket::~Socket() {
    printf("~[socket]: fd = %d\n", fd);
    close_socket();
}

/* PUBLIC FUNCTIONS */

void Socket::read_some(const buffer_ptr buffer, ReadHandler handler) {
    set_buffer(buffer);
    read_some(handler);
}
void Socket::read_some(ReadHandler handler) {
    buffer->clear();
    while(true) {
        ssize_t received = recv(fd, tmp, MAX_BUFFER_SIZE, 0);
        if (received <= 0) {
            //log_error("Error reading from socket", ERROR_MESSAGE);
            handler(received, buffer->size());
            break;
        } else {
            //printf("appending %d bytes\n", (int)received);
            buffer->append(tmp, received);
        }
    }
    set_writable();
}

void Socket::write_some(const buffer_ptr buffer, WriteHandler handler) {
    set_buffer(buffer);
    write_some(handler);
}
void Socket::write_some(WriteHandler handler) {
    int ptr = 0;
    while(ptr < buffer->size()) {
        int len = std::min(MAX_BUFFER_SIZE - 1, (int)buffer->size() - ptr);
        strncpy(tmp, buffer->substr(ptr, len).c_str(), sizeof(tmp));
        tmp[sizeof(tmp)] = 0;
        if (send(fd, tmp, len + 1, 0) != len + 1) {
            log_error("Could not write to stream", ERROR_MESSAGE);
            handler(1, ptr);
            break;
        }
        ptr += len;
    }
    //set_readable();
    close_socket();
    handler(0, buffer->size());
}

int Socket::set_nonblocking() {
    int flags = 0;
    if ((flags = fcntl(this->fd, F_GETFL, 0)) == -1) {
        flags = 0;
    }
    return fcntl(this->fd, F_SETFL, flags | O_NONBLOCK);
}

int Socket::close_socket() {
    if (fd != 1) {
        close(fd);
        fd = -1;
        return 0;
    }
    return -1;
}

/* PRIVATE FUNCTIONS */

Socket::buffer_ptr Socket::get_buffer() const {
    return this->buffer;
}

void Socket::set_buffer(const Socket::buffer_ptr other) {
    this->buffer = other;
}

int Socket::set_readable() {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (epoll_ctl(this->io->epfd, EPOLL_CTL_MOD, fd, &event) < 0) {
        log_error("Failed to set_readable()", ERROR_MESSAGE);
        return -1;
    }
    return 0;
}

int Socket::set_writable() {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT;
    if (epoll_ctl(this->io->epfd, EPOLL_CTL_MOD, fd, &event) < 0) {
        log_error("Failed to set_writable()", ERROR_MESSAGE);
        return -1;
    }
    return 0;
}