#include "ioloop.h"
#include "handler.h"
#include "debug.h"

IOLoop::IOLoop() {
    this->stopped = true;
    if((epfd = epoll_create(EPOLL_EVENTS)) == -1) {
        log_error("Failed to create epoll", FATAL_ERROR);
    }
    try {
        handlers = new void*[HANDLERS_MAX_SIZE];
        events = new epoll_event[MAX_EVENTS];
    } catch(...) {
        delete[] handlers;
    }
}
IOLoop::~IOLoop() {
    printf("IOLoop: destructor\n");
    for(int i = 0; i < (int)fds.size(); i++) {
        IOLoop::Instance()->remove_handler(fds[i]);
    }
    delete[] handlers;
    delete[] events;
}

IOLoop* IOLoop::Instance(){
    static IOLoop loop;
    return &loop;
}

void IOLoop::start() {
    signal(SIGINT, IOLoop::signal_int);
    this->stopped = false;
    while(!this->stopped) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        for(int i = 0; i < nfds; ++i) {
            int fd = events[i].data.fd;
            Handler* handler = (Handler*)handlers[fd];
            if(!handler) {
                log_error("IOLoop: event handler not present", ERROR_MESSAGE);
                continue;
            }
            handler->handle(events[i]);
        }
    }
}
void IOLoop::stop() {
    this->stopped = true;
}

void IOLoop::add_handler(int fd, void* handler, unsigned int events) {
    if (std::find(fds.begin(), fds.end(), fd) == fds.end()) {
        //printf("fds.push_back(%d)\n", fd);
        fds.push_back(fd);
    }
    handlers[fd] = handler;

    epoll_event event;
    event.data.fd = fd;
    event.events = events;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) < 0) {
        log_error("Failed to insert handler to epoll", ERROR_MESSAGE);
        log_epoll_event(event);
    }
}

void IOLoop::update_handler(int fd, unsigned int events) {
    if (!handlers[fd]) {
        log_error("IOLoop:update_handler: handler of a non registered file descriptor", ERROR_MESSAGE);
        return;
    }
    epoll_event event;
    event.data.fd = fd;
    event.events = events;
    if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &event) < 0) {
        log_error("IOLoop:update_handler: failed to modify epoll events", ERROR_MESSAGE);
        log_epoll_event(event);
    }
}

void IOLoop::remove_handler(int fd) {
    if (!handlers[fd]) {
        log_error("IOLoop:remove_handler: handler of a non registered file descriptor", ERROR_MESSAGE);
        return;
    }

    epoll_event event;
    event.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event) < 0) {
        log_error("IOLoop:remove_handler: failed to modify epoll events", ERROR_MESSAGE);
        log_epoll_event(event);
    }

    fds.erase(std::find(fds.begin(), fds.end(), fd));
    delete (Handler*)handlers[fd];
}

void IOLoop::signal_int(int x) {
    printf("IOLoop: SIGINT received, exiting...\n");
    IOLoop::Instance()->stop();
}
