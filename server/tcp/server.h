#ifndef SERVER_H
#define SERVER_H
#include "../headers.h"
#include "io_service.h"

struct Socket;
struct IO_Service;

struct Server {
public:
    friend struct IO_Service;
    friend struct Socket;
    #define MAX_PENDING 100
    typedef std::shared_ptr<Socket> socket_ptr;
    typedef std::shared_ptr<IO_Service> io_service_ptr;
    typedef std::shared_ptr<Server> server_ptr;

    Server(io_service_ptr io, const int port);
    virtual ~Server();

    int accept1(socket_ptr socket);
private:
    io_service_ptr io;
    socket_ptr _socket;
    int port;
};
#endif
