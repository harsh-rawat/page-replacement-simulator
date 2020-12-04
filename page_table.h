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
#include "fifo_page_replacement.h"

void RunSimulation(char *filepath, void *process_root, void *ipt_root, statistics *stats);

#endif
