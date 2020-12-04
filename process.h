#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H

#include "statistics.h"
#include "tsearch.h"
#include "input_parser.h"
#include "page_table.h"
#include "error_handler.h"

typedef struct active_process {
    int pid;
    int unblock_time;
    int unblock_page_frame;
    page_table_entry *unblock_page_table_entry;
    doubly_linked_list *next;
} active_process;

struct process {
    int pid;
    long end;
    void *page_table;
    active_process *current_process;
};

typedef struct process process;

void *ParseTraceFile(char *filepath, statistics *stats);

process *create_process(int pid, long file_ptr);

int compare_memory_trace_process(const void *a, const void *b);

active_process *CreateActiveProcess(int pid);

#endif //PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H
