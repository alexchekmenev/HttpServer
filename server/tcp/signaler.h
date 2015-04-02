#include "io_service.h"

#ifndef SIGNALER_H
#define SIGNALER_H

struct Signaler {
public:
    typedef std::function<void(int)> signal_handler;

    static void register_service(IO_Service* io);
    static void unregister_service();
    static void register_signal(int signal, void (*handler)(int));
    static void unregister_signal(int signal);

    static void signal_int(int signal);
    static void signal_abrt(int signal);
private:

    static IO_Service* io;
};


#endif