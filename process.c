#include <stdlib.h>
#include <stdio.h>
#include "process.h"

void *ParseTraceFile(char *filepath, statistics *stats) {
    FILE *file = fopen(filepath, "r");
    int lineIndex = 0;
    void *root = NULL;
    long file_ptr = ftell(file);

    while (feof(file) == 0) {
        memory_reference *mem_reference = ReadLine(file, file_ptr);
        //Check if the process id exists in the hashtable
        process *reference_process = create_process(mem_reference->pid, file_ptr);
        process *existing_process = Get(&root, reference_process,
                                        &compare_memory_trace_process);//Get the process from hashtable
        if (existing_process == NULL) {//If process does not exist in hashtable
            //Put this new process in hashtable
            Put(&root, reference_process, &compare_memory_trace_process);
        } else {//Take the existing process object and update the last value
            free(reference_process);
            existing_process->end = file_ptr;
        }
        free(mem_reference);
        file_ptr = ftell(file);
        lineIndex++;
    }
    UpdateTotalMemoryReferences(stats, lineIndex);
    return root;
}

active_process *CreateActiveProcess(int pid) {
    active_process *new_process = malloc(sizeof(active_process));
    new_process->pid = pid;
    new_process->unblock_time = 0;
    new_process->unblock_page_frame = -1;
    new_process->unblock_page_table_entry = NULL;
    new_process->next = CreateLinkedList();
//    AddNode(new_process->next, pid);
    return new_process;
}

process *create_process(int pid, long file_ptr) {
    process *new_process = malloc(sizeof(process));
    new_process->pid = pid;
    new_process->end = file_ptr;
    new_process->page_table = NULL;
    new_process->current_process = CreateActiveProcess(pid);
    return new_process;
}

// Returns -1 if a <  b
// Returns 1  if a >  b
// Returns 0  if a == b
int compare_memory_trace_process(const void *a, const void *b) {
    process *node_a = (process *) a;
    process *node_b = (process *) b;

    if (node_a->pid < node_b->pid)
        return -1;
    else if (node_a->pid > node_b->pid)
        return 1;
    else
        return 0;
}
