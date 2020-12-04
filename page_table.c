#include <stdlib.h>
#include <stdio.h>
#include "page_table.h"


void perform_initial_tasks(void *ipt_root, Queue *disk_queue, Heap *runnable_processes, void **blocked_processes,
                           int clock_time);

void update_statistics(statistics *stats, int occupied_pf, int non_blocked, int is_page_fault, int update_clock_tick);

process *get_process_from_bst(void *process_root, memory_reference *mem_reference);

void handle_page_fault(Queue *disk_queue, int clock, void **blocked_processes, process *existing_process, long file_ptr,
                       page_table_entry *existing_pte, int is_blocked, statistics *stats,
                       running_process_tracker *runnable_tracker);

page_table_entry *create_page_table_entry(int vpn);

running_process_tracker *create_running_process_tracker();

int compare_memory_trace_page_table_entry(const void *a, const void *b);

int compare_memory_trace_active_process(const void *a, const void *b);

void free_process_page_frames(process *current_process, running_process_tracker *runnable_tracker);

/**
 * Code starts from below!
 * */

void RunSimulation(char *filepath, void *process_root, void *ipt_root, statistics *stats) {
    //A clock for this simulation
    int clock = 1;

    //A min-heap for current process and older process which were blocked.
    Heap *runnable_processes = CreateHeap();

    //A tree for blocked processes. It will have all active processes in it.
    void *blocked_processes = NULL;

    //A queue for disk operations. If this queue is empty then no process is blocked.
    Queue *disk_queue = CreateQueue();

    FILE *file = fopen(filepath, "r");
    long curr_file_pointer = ftell(file);

    running_process_tracker *runnable_tracker = create_running_process_tracker();

    while (!IsEmptyQueue(disk_queue) || feof(file) == 0) {
        //Perform some bookkeeping tasks along with disk_queue update
        perform_initial_tasks(ipt_root, disk_queue, runnable_processes, &blocked_processes, clock);

        active_process *current_process = NULL;
        memory_reference *mem_reference = NULL;

        if (!IsEmptyHeap(runnable_processes)) {
            current_process = ExtractMin(runnable_processes);
            int next_file_ptr = (int) GetNext(current_process->next);

            mem_reference = ReadLineAtIndex(file, next_file_ptr - 1);
            fseek(file, curr_file_pointer, SEEK_SET);
        } else if (feof(file) == 0) {
            mem_reference = ReadLine(file, curr_file_pointer);
            if (mem_reference == NULL) {
                continue;
            }
            curr_file_pointer = ftell(file);
        } else if (IsEmptyQueue(disk_queue)) {
            //If blocked queue is empty as well then it means the simulation has ended
            break;
        } else {
            //Get stats of non-blocked and occupied pf from page replacement algo and update here
            update_statistics(stats, GetOccupiedPageFrames(page_replacement_algo), 0, 0, 1);
            //If we don't have any process in runnable state and trace has ended
            //then wait for blocked process to become runnable
            clock++;
            continue;
        }

        process *existing_process = get_process_from_bst(process_root, mem_reference);

        //Is the current memory reference process blocked
        if (Get(&blocked_processes, existing_process->current_process, &compare_memory_trace_active_process) != NULL) {
            //Handle page fault but only add current reference to the end of next list
            handle_page_fault(disk_queue, clock, &blocked_processes, existing_process, mem_reference->file_ptr, NULL,
                              1, stats, runnable_tracker);
        } else {

            page_table_entry *reference_page_table_entry = create_page_table_entry(mem_reference->vpn);
            page_table_entry *existing_page_table_entry = Get(&existing_process->page_table, reference_page_table_entry,
                                                              compare_memory_trace_page_table_entry);
            if (existing_page_table_entry == NULL) { //This signifies page fault
                // Put the value in the page table
                Put(&existing_process->page_table, reference_page_table_entry, &compare_memory_trace_page_table_entry);
                // handle page fault
                handle_page_fault(disk_queue, clock, &blocked_processes, existing_process, mem_reference->file_ptr,
                                  reference_page_table_entry, 0, stats, runnable_tracker);
            } else {
                if (existing_page_table_entry->page_frame == NULL) { //Again this means page fault
                    handle_page_fault(disk_queue, clock, &blocked_processes, existing_process, mem_reference->file_ptr,
                                      existing_page_table_entry, 0, stats, runnable_tracker);
                } else { // This means page hit
                    //First let the page replacement algorithm know which page was accessed
                    UpdateAccessedPageFrame(page_replacement_algo, existing_page_table_entry->page_frame->ppn_id);
                    //Now this process is in the runnable state
                    if (Get(&runnable_tracker->list_processes, existing_process, &compare_memory_trace_process) ==
                        NULL) {
                        Put(&runnable_tracker->list_processes, existing_process, &compare_memory_trace_process);
                        runnable_tracker->running += 1;
                    }

                    void *next_ptr = GetNext(existing_process->current_process->next);
                    if (next_ptr != NULL && (long) next_ptr == mem_reference->file_ptr + 1)
                        DeleteFromFront(existing_process->current_process->next);
                    //Add the next readable line for the existing process (In case it was previously blocked)
                    if (GetNext(existing_process->current_process->next) != NULL) {
                        //There is a line which needs to be read before moving to current line
                        AddToHeap(runnable_processes, (int) GetNext(existing_process->current_process->next),
                                  existing_process->current_process);
                    }
//                    if (curr_file_pointer == existing_process->end) {
                    if (mem_reference->file_ptr == existing_process->end) {
                        //Clean up all the page frames of the existing process
                        //Integrate this with PRA
                        free_process_page_frames(existing_process, runnable_tracker);
                        //Current evicted process was runnable for this clock cycle
                        UpdateAverageRunnableProcesses(stats, 1);
                    }
                }
                free(reference_page_table_entry);
            }
            clock++;
            //Get stats of non-blocked and occupied pf from page replacement algo and update here
            update_statistics(stats, GetOccupiedPageFrames(page_replacement_algo), runnable_tracker->running, 0, 1);
        }

        free(mem_reference);
    }
}

void update_statistics(statistics *stats, int occupied_pf, int non_blocked, int is_page_fault, int update_clock_tick) {
    UpdateAverageMemoryUtilization(stats, occupied_pf);
    UpdateAverageRunnableProcesses(stats, non_blocked);
    if (update_clock_tick)
        UpdateRunningTime(stats);
    if (is_page_fault)
        UpdateTotalPageFaults(stats);
}

void free_process_page_frames(process *current_process, running_process_tracker *runnable_tracker) {
    if (Remove(&runnable_tracker->list_processes, current_process, &compare_memory_trace_process))
        runnable_tracker->running -= 1;
    TraverseTree(current_process->page_table, &Callback_free_page_frames);
}

void handle_page_fault(Queue *disk_queue, int clock, void **blocked_processes, process *existing_process, long file_ptr,
                       page_table_entry *existing_pte, int is_blocked, statistics *stats,
                       running_process_tracker *runnable_tracker) {
    active_process *current_process = existing_process->current_process;
    void *next_ptr = GetNext(current_process->next);
    if (next_ptr == NULL || (long) next_ptr != file_ptr + 1)
        AddToBack(current_process->next, file_ptr + 1, 0);

    if (!is_blocked) {
        active_process *blocked_process_from_queue = GetFromQueueEnd(disk_queue);
        //Call Page Replacement Algorithm to find the page which needs to be replaced
        int replace_page_frame = GetReplacementPage(page_replacement_algo);
        current_process->unblock_page_frame = replace_page_frame;
        current_process->unblock_page_table_entry = existing_pte;
        AddToQueue(disk_queue, current_process);
        if (blocked_process_from_queue == NULL)
            current_process->unblock_time = clock + DISK_ACCESS_TIME + 1;
        else
            current_process->unblock_time = blocked_process_from_queue->unblock_time + DISK_ACCESS_TIME;

        Put(blocked_processes, current_process, &compare_memory_trace_active_process);

        if (Remove(&runnable_tracker->list_processes, current_process, &compare_memory_trace_process))
            runnable_tracker->running -= 1;

        update_statistics(stats, 0, 0, 1, 0);
    }
}

void perform_initial_tasks(void *ipt_root, Queue *disk_queue, Heap *runnable_processes,
                           void **blocked_processes, int clock_time) {
    //Update the queue and move any process to runnable if required
    active_process *curr_process = (active_process *) GetFromQueue(disk_queue);
    if (curr_process != NULL && curr_process->unblock_time == clock_time) {
        //While unblocking, ensure that the page frame is replaced
        Unlink_pf_pte(ipt_root, curr_process->unblock_page_frame);
        Link_pf_pte(ipt_root, curr_process->unblock_page_frame, curr_process->unblock_page_table_entry);
        //Remove from Queue
        RemoveFromQueue(disk_queue);
        AddToHeap(runnable_processes, (int) GetNext(curr_process->next), curr_process);
        Remove(blocked_processes, curr_process, &compare_memory_trace_active_process);
    }
}

process *get_process_from_bst(void *process_root, memory_reference *mem_reference) {
    process *reference_process = create_process(mem_reference->pid, 0);
    process *existing_process = Get(&process_root, reference_process,
                                    &compare_memory_trace_process);//Get the process from hashtable

    if (existing_process == NULL) {
        // Throw error as you expect the process to be present
        InvalidInputError(-1);
    }

    free(reference_process);
    return existing_process;
}

page_table_entry *create_page_table_entry(int vpn) {
    page_table_entry *new_page_table_entry = malloc(sizeof(page_table_entry));
    new_page_table_entry->vpn = vpn;
    new_page_table_entry->page_frame = NULL;
    return new_page_table_entry;
}

running_process_tracker *create_running_process_tracker() {
    running_process_tracker *running = malloc(sizeof(running_process_tracker));
    running->running = 0;
    running->list_processes = NULL;
    return running;
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