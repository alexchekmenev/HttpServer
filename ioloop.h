#ifndef _IOLOOP_H
#define _IOLOOP_H
#include "headers.h"

#define EPOLL_EVENTS 1024
#define MAX_EVENTS 1000
#define HANDLERS_MAX_SIZE 1000

struct IOLoop {
public:
    IOLoop();
    ~IOLoop();
    static IOLoop* Instance();
    void start();
    void stop();
    void add_handler(int fd, void* handler, unsigned int events);
    void update_handler(int fd, unsigned int events);
    void remove_handler(int fd);
private:
    static void signal_int(int signum);

    bool stopped;
    epoll_event* events;
    void** handlers;
    int epfd;
public:
    std::vector<int> fds;
};

#endif

