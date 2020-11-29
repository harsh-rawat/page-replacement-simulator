#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_INPUT_PARSER_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_INPUT_PARSER_H

#include "error_handler.h"

#define MAX_BUFFER_SIZE 4096

struct memory_reference{
    int pid;
    int vpn;
};
typedef struct memory_reference memory_reference;

memory_reference* ReadLine(FILE *file, int index);
#endif
