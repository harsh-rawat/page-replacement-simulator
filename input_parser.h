#ifndef ASSIGNMENT4_INPUT_PARSER_H
#define ASSIGNMENT4_INPUT_PARSER_H

#include "error_handler.h"

#define MAX_BUFFER_SIZE 4096

struct memory_reference{
    int pid;
    int vpn;
};
typedef struct memory_reference memory_reference;

memory_reference* ReadLine(FILE *file, int index);
#endif
