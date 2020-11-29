#ifndef ASSIGNMENT4_PROCESS_H
#define ASSIGNMENT4_PROCESS_H

#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"

struct process {
    int pid;
    int start;
    int end;
};
typedef struct process process;

void* ParseTraceFile(char* filepath);

#endif
