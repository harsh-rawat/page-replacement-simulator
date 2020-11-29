#include <stdlib.h>
#include <stdio.h>
#include "page_table.h"
#include "process.h"

void *ParseTraceFile2(char *filepath, void* ipt_root) {
    FILE *file = fopen(filepath, "r");
    int lineIndex = 0;
    void *root = NULL;

    while (feof(file) == 0) {
        memory_reference *mem_reference = ReadLine(file, lineIndex);
        // Check if the process_id is under blocked processes. If so, maintain the pointer
        // to this line and continue

        process *reference_process = create_process(mem_reference->pid, lineIndex);
        process *existing_process = Get(&root, reference_process,
                                        &compare_memory_trace_process);//Get the process from hashtable
        if (existing_process == NULL) {
            free(reference_process);
            // Throw error as you expect the process to be present
            InvalidInputError(lineIndex);
        }

        page_table_entry *reference_page_table_entry = create_page_table_entry(mem_reference->vpn);
        page_table_entry *existing_page_table_entry = Get(&existing_process->page_table, reference_page_table_entry,
                                                          compare_memory_trace_page_table_entry);
        free(mem_reference);
        if (existing_page_table_entry == NULL) { //This signifies page fault
            // Put the value in the page table
            Put(&existing_process->page_table, reference_page_table_entry, &compare_memory_trace_page_table_entry);
        } else {
            free(reference_page_table_entry);
            if(existing_page_table_entry->page_frame == NULL){ //Again this means page fault

            } else { // This means page hit
                //Increment the clock by 1 and continue to next line
            }
        }
        lineIndex++;
    }
    return root;
}

page_table_entry *create_page_table_entry(int vpn) {
    page_table_entry *new_page_table_entry = malloc(sizeof(page_table_entry));
    new_page_table_entry->vpn = vpn;
    new_page_table_entry->page_frame = NULL;
    return new_page_table_entry;
}

int compare_memory_trace_page_table_entry(const void *a, const void *b) {
    page_table_entry *node_a = (page_table_entry *) a;
    page_table_entry *node_b = (page_table_entry *) b;

    if (node_a->vpn < node_b->vpn)
        return -1;
    else if (node_a->vpn > node_b->vpn)
        return 1;
    else
        return 0;
}
