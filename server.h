#ifndef SERVER_H
#define SERVER_H
#include "headers.h"
#include "ioloop.h"
#include "handler.h"
#include "client.h"

#define MAX_PENDING 100

struct Server: public Handler {
    Server(int port);
    Server(Server* other);
    virtual ~Server();

    int handle(epoll_event e);
    virtual void onConnected(Client* client);
};
#endif
