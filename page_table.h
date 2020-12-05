/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H

#include "queue.h"
#include "heap.h"
#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"
#include "inverted_page_table.h"
#include "tables.h"
#include "process.h"
#include "statistics.h"

typedef struct running_process_tracker {
    int running;
    void *list_processes;
} running_process_tracker;

void RunSimulation(char *filepath, void *process_root, void *ipt_root, statistics *stats);

#endif
