//
// Created by Sidharth Gurbani on 11/28/20.
//

#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H

#include "tsearch.h"
#include "input_parser.h"
#include "error_handler.h"

typedef struct page_table_entry {
    int vpn;
    void* PF;
} page_table_entry;

page_table_entry* create_page_table_entry(int vpn);
int compare_memory_trace_page_table_entry(const void *a, const void *b);

#endif //PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H
