#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H

#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"

struct process {
    int pid;
    int start;
    int end;
    void *page_table;
};
typedef struct process process;

void *ParseTraceFile(char *filepath);

process *create_process(int pid, int index);

int compare_memory_trace_process(const void *a, const void *b);

#endif
