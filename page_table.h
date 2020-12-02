#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H

#define DISK_ACCESS_TIME 2000000

#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"
#include "inverted_page_table.h"
#include "tables.h"

/*
typedef struct page_table_entry {
    int vpn;
    page_frame *page_frame;
}page_table_entry;
 */

void RunSimulation(char *filepath, void *process_root, void *ipt_root);
#endif
