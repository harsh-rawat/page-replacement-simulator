#ifndef PAGE_REPLACEMENT_SIMULATOR_TABLES_H
#define PAGE_REPLACEMENT_SIMULATOR_TABLES_H

#include "fifo_page_replacement.h"

#define DISK_ACCESS_TIME 2000000

typedef struct page_frame page_frame;

typedef struct {
    int vpn;
    page_frame *page_frame;
} page_table_entry;

struct page_frame {
    int ppn_id;
    page_table_entry *page_table_entry;
};

#endif
