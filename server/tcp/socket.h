#ifndef SOCKET_H
#define SOCKET_H

#include "../headers.h"
#include "io_service.h"

typedef std::function<void(const int& code, const int& bytes_transferred)> ReadHandler;
typedef std::function<void(const int& code, const int& bytes_transferred)> WriteHandler;

struct IO_Service;

struct Socket {
public:
    friend struct IO_Service;
    friend struct Server;
    #define MAX_BUFFER_SIZE 5
    typedef std::shared_ptr<Socket> socket_ptr;
    typedef std::shared_ptr<IO_Service> io_service_ptr;
    typedef std::shared_ptr<std::string> buffer_ptr;

    Socket(io_service_ptr io, const int& fd, const sockaddr_in& addr);
    virtual ~Socket();

    int set_nonblocking();
    void read_some(ReadHandler handler);
    void read_some(const buffer_ptr buffer, ReadHandler handler);
    void write_some(WriteHandler handler);
    void write_some(const buffer_ptr buffer, WriteHandler handler);
    int close_socket();
private:
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
