/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H
#define PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H

#include "error_handler.h"

#define MEGA 1024*1024

struct options {
    int p;
    int m;
    char *filepath;
};

typedef struct options options;

options *process_options(int argc, char *argv[]);

#endif //PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H
