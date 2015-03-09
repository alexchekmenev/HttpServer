#include "signaler.h"


IO_Service::io_service_ptr Signaler::io;

void Signaler::register_service(IO_Service::io_service_ptr _io) {
    Signaler::io = _io;
}

void Signaler::signal_int(int signal) {
    printf("SIGINT occured. Stopping io_service...\n");
    io->stop();
}
void Signaler::signal_abrt(int signal) {
    printf("SIGABRT occured. Stopping io_service...\n");
    io->stop();
}

