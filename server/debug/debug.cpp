#include "debug.h"

void log_error(const char *m, int level) {
    if(level & FATAL_ERROR) {
        perror("FATAL ERROR: ");
    } else if (level & ERROR_MESSAGE) {
        perror("ERROR: ");
    }
    perror(m);
    if(level & FATAL_ERROR) {
        exit(1);
    }
}

