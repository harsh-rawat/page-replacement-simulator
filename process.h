#ifndef ASSIGNMENT4_PROCESS_H
#define ASSIGNMENT4_PROCESS_H

#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"

struct process {
    int pid;
    int start;
    int end;
    void* PT;
};
typedef struct process process;

void* ParseTraceFile(char* filepath);
process* create_process(int pid, int index);
int compare_memory_trace_process(const void *a, const void *b);
#endif
