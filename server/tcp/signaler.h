#include "io_service.h"

#ifndef SIGNALER_H
#define SIGNALER_H

struct Signaler {
public:
    static void register_service(IO_Service::io_service_ptr io);
    static void signal_int(int signal);
    static void signal_abrt(int signal);
private:
    static IO_Service::io_service_ptr io;
};


#endif