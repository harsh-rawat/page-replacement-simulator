#include <stdlib.h>
#include <stdio.h>
#include "page_table.h"
#include "queue.h"
#include "heap.h"

void perform_initial_tasks(void *ipt_root, Queue *disk_queue, Heap *runnable_processes, void *blocked_processes,
                           int clock_time);

process *get_process_from_bst(void *process_root, memory_reference *mem_reference);

void handle_page_fault(int clock, void *blocked_processes, process *existing_process, int lineIndex,
                       page_table_entry *existing_pte, int is_blocked);

page_table_entry *create_page_table_entry(int vpn);

int compare_memory_trace_page_table_entry(const void *a, const void *b);

int compare_memory_trace_active_process(const void *a, const void *b);

void RunSimulation(char *filepath, void *process_root, void *ipt_root) {
    //A clock for this simulation
    int clock = 0;

    //A min-heap for current process and older process which were blocked.
    Heap *runnable_processes = CreateHeap();

    //A tree for blocked processes. It will have all active processes in it.
    void *blocked_processes = NULL;

    //A queue for disk operations. If this queue is empty then no process is blocked.
    Queue *disk_queue = CreateQueue();

    FILE *file = fopen(filepath, "r");
    int lineIndex = 0;

    while (!IsEmptyQueue(disk_queue) || feof(file) == 0) {
        //Perform some bookkeeping tasks along with disk_queue update
        perform_initial_tasks(ipt_root, disk_queue, runnable_processes, blocked_processes, clock);

        active_process *current_process = NULL;
        memory_reference *mem_reference = NULL;
        if (!IsEmptyHeap(runnable_processes)) {
            current_process = ExtractMin(runnable_processes);
            int next_line_number = GetNext(current_process->next);
            mem_reference = ReadLineAtIndex(file, next_line_number);
            DeleteNode(current_process->next, next_line_number);
        } else if (feof(file) == 0) {
            mem_reference = ReadLine(file, lineIndex);
            lineIndex++;
        }
        if (IsEmptyQueue(disk_queue)) {
            //If blocked queue is empty as well then it means the simulation has ended
            break;
        } else {
            //If we don't have any process in runnable state and trace has ended
            //then wait for blocked process to become runnable
            clock++;
            continue;
        }

        process *existing_process = get_process_from_bst(process_root, mem_reference);

        //Is the current memory reference process blocked
        if (Get(&blocked_processes, existing_process->current_process, &compare_memory_trace_active_process) != NULL) {
            //Handle page fault but only add current reference to the end of next list
            handle_page_fault(clock, blocked_processes, existing_process, mem_reference->lineIndex, NULL, 1);
        } else {

            page_table_entry *reference_page_table_entry = create_page_table_entry(mem_reference->vpn);
            page_table_entry *existing_page_table_entry = Get(&existing_process->page_table, reference_page_table_entry,
                                                              compare_memory_trace_page_table_entry);
            if (existing_page_table_entry == NULL) { //This signifies page fault
                // Put the value in the page table
                Put(&existing_process->page_table, reference_page_table_entry, &compare_memory_trace_page_table_entry);
                // handle page fault
                handle_page_fault(clock, blocked_processes, existing_process, mem_reference->lineIndex,
                                  reference_page_table_entry, 0);
            } else {
                if (existing_page_table_entry->page_frame == NULL) { //Again this means page fault
                    handle_page_fault(clock, blocked_processes, existing_process, mem_reference->lineIndex,
                                      existing_page_table_entry, 0);
                } else { // This means page hit
                    //Add the next readable line for the existing process (In case it was previously blocked)
                    if (GetNext(existing_process->current_process->next) != NULL) {
                        //There is a line which needs to be read before moving to current line
                        AddToHeap(runnable_processes, (int) GetNext(existing_process->current_process->next),
                                  existing_process->current_process);
                    }
                    if (lineIndex == existing_process->end) {
                        //To-do: Clean up all the page frames of the existing process
                    }
                }
                free(reference_page_table_entry);
            }
        }
        free(mem_reference);
        clock++;
    }
}

void free_process_page_frames() {
//STep 1: Write twalk functionality in tsearch
//Use that to go over all the page_table_entries and free the page frames
}

void handle_page_fault(int clock, void *blocked_processes, process *existing_process, int lineIndex,
                       page_table_entry *existing_pte, int is_blocked) {
    active_process *current_process = existing_process->current_process;
    AddNode(current_process->next, lineIndex);
    if (!is_blocked) {
        //To-do: Call Page Replacement Algorithm to find the page which needs to be replaced
        int replace_page_frame = GetPageToReplace();
        current_process->unblock_page_frame = replace_page_frame;
        current_process->unblock_page_table_entry = existing_pte;
        AddToQueue(disk_queue, current_process);
        current_process->unblock_time = clock + DISK_ACCESS_TIME;
        Put(&blocked_processes, existing_process, &compare_memory_trace_process);
    }
}

void perform_initial_tasks(void *ipt_root, Queue *disk_queue, Heap *runnable_processes, void *blocked_processes,
                           int clock_time) {
    //Update the queue and move any process to runnable if required
    active_process *curr_process = (active_process *) GetFromQueue(disk_queue);
    if (curr_process != NULL && curr_process->unblock_time == clock_time) {
        //While unblocking, ensure that the page frame is replaced
        Unlink_pf_pte(ipt_root, curr_process->unblock_page_frame);
        Link_pf_pte(ipt_root, curr_process->unblock_page_frame, curr_process->unblock_page_table_entry);
        //Remove from Queue
        RemoveFromQueue(disk_queue);
        AddToHeap(runnable_processes, (int) GetNext(curr_process->next), curr_process);
        Remove(&blocked_processes, curr_process, &compare_memory_trace_active_process);
    }
}

process *get_process_from_bst(void *process_root, memory_reference *mem_reference) {
    process *reference_process = create_process(mem_reference->pid, 0);
    process *existing_process = Get(&process_root, reference_process,
                                    &compare_memory_trace_process);//Get the process from hashtable
    free(reference_process);
    if (existing_process == NULL) {
        // Throw error as you expect the process to be present
        InvalidInputError(-1);
    }

    return existing_process;
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

int compare_memory_trace_active_process(const void *a, const void *b) {
    active_process *node_a = (active_process *) a;
    active_process *node_b = (active_process *) b;

    if (node_a->pid < node_b->pid)
        return -1;
    else if (node_a->pid > node_b->pid)
        return 1;
    else
        return 0;
}