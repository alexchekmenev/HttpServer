#ifndef CLIENT_H
#define CLIENT_H
#include "headers.h"
#include "handler.h"
#include "client.h"
#include "ioloop.h"

#define BUFFER_SIZE 1000

struct Client: public Handler {
public:
    Client(int fd, sockaddr_in addr);
    Client(Client* other);
    virtual ~Client();
    int handle(epoll_event e);
private:
    char* buffer;
    int received;
};

#endif

