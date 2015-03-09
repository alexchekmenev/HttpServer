#include "debug.h"

void log_epoll_event(epoll_event e) {
    printf("EVENT (fd: %d, events:\n", e.data.fd);
    if(e.events & EPOLLERR)
        printf("   EPOLLERR\n");
    if(e.events & EPOLLET)
        printf("   EPOLLET\n");
    if(e.events & EPOLLHUP)
        printf("   EPOLLHUP\n");
    if(e.events & EPOLLIN)
        printf("   EPOLLIN\n");
    if(e.events & EPOLLONESHOT)
        printf("   EPOLLONESHOT\n");
    if(e.events & EPOLLOUT)
        printf("   EPOLLOUT\n");
    if(e.events & EPOLLPRI)
        printf("   EPOLLPRI\n");
}

void log_error(const char *m, int level) {
    if(level & FATAL_ERROR)
        perror("FATAL ERROR: ");
    else if(level & ERROR_MESSAGE)
        perror("ERROR: ");
    perror(m);

    if(level & FATAL_ERROR)
        exit(1);
}

