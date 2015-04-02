#include "signaler.h"

IO_Service* Signaler::io;

void Signaler::register_service(IO_Service* _io) {
    Signaler::io = _io;
}

void Signaler::unregister_service() {
    Signaler::io = nullptr;
}


void Signaler::register_signal(int signal, void (*handler)(int)) {
    static struct sigaction term;
    term.sa_handler = handler;
    term.sa_flags = SA_SIGINFO;
    if (sigaction(signal, &term, NULL) == -1) {
        throw std::runtime_error("Could not connect signal");
    }
}

void Signaler::unregister_signal(int signal) {
    static struct sigaction term;
    term.sa_handler = SIG_DFL;
    term.sa_flags = SA_SIGINFO;
    if (sigaction(signal, &term, NULL) == -1) {
        throw std::runtime_error("Could not connect signal");
    }
}


void Signaler::signal_int(int signal) {
    printf("\nSIGINT occured. Stopping HttpServer...\n");
    io->stop();
}
void Signaler::signal_abrt(int signal) {
    printf("\nSIGABRT occured. Stopping HttpServer...\n");
    io->stop();
}

