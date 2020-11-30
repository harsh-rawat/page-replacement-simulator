#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_PROCESS_H

#include "linked_list.h"
#include "tsearch.h"
#include "input_parser.h"
#include "page_table.h"
#include "error_handler.h"

typedef struct active_process {
    int pid;
    int unblock_time;
    int unblock_page_frame;
    page_table_entry *unblock_page_table_entry;
    list_node *next;
} active_process;

struct process {
    int pid;
    int end;
    void *page_table;
    active_process *current_process;
};

typedef struct process process;

void *ParseTraceFile(char *filepath);

process *create_process(int pid, int index);

int compare_memory_trace_process(const void *a, const void *b);

active_process *CreateActiveProcess(int pid);

#endif
