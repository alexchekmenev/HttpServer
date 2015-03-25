#ifndef SOCKET_H
#define SOCKET_H

#include "../headers.h"
#include "io_service.h"

typedef std::function<void(const int& code, const int& bytes_transferred)> Handler;

struct IO_Service;

struct Socket {
public:
    #define MAX_BUFFER_SIZE 4096

    friend struct IO_Service;
    friend struct Server;

    typedef std::shared_ptr<Socket> socket_ptr;
    typedef std::shared_ptr<IO_Service> io_service_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    Socket(io_service_ptr io, const int& fd, const sockaddr_in& addr);
    virtual ~Socket();

    int set_nonblocking();
    void read_some(Handler handler);
    void read_some(const buffer_ptr buffer, Handler handler);
    void write_some(Handler handler);
    void write_some(const buffer_ptr buffer, Handler handler);
private:
    int close_socket();
    buffer_ptr get_buffer() const;
    void set_buffer(const buffer_ptr other);

    int set_readable();
    int set_writable();

    int fd;
    sockaddr_in addr;
    char tmp[MAX_BUFFER_SIZE];
    buffer_ptr buffer;
    io_service_ptr io;
};

#endif
