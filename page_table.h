#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_TABLE_H

#define DISK_ACCESS_TIME 2000000

#include "tsearch.h"
#include "input_parser.h"
#include "inverted_page_table.h"
#include "error_handler.h"
#include "process.h"

typedef struct page_table_entry {
    int vpn;
    page_frame *page_frame;
} page_table_entry;

#endif
