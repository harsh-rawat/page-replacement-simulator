//
// Created by Sidharth Gurbani on 12/1/20.
//

#ifndef PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H
#define PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H

#define MEGA 1024*1024

struct options {
    int p;
    int m;
    char* filepath;
};

typedef struct options options;
options* process_options(int argc, char* argv[]);
#endif //PAGE_REPLACEMENT_SIMULATOR_PROCESS_OPTIONS_H
