#ifndef HANDLER_H
#define HANDLER_H
#include "headers.h"

#define MAX_PENDING 100

struct Handler {
public:
    Handler();
    Handler(int fd, sockaddr_in addr);
    virtual ~Handler();

    int set_nonblocking();
    virtual int handle(epoll_event e);

    int fd;
    sockaddr_in addr;
};
#endif
