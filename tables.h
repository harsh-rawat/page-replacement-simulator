//
// Created by Sidharth Gurbani on 12/1/20.
//

#ifndef PAGE_REPLACEMENT_SIMULATOR_TABLES_H
#define PAGE_REPLACEMENT_SIMULATOR_TABLES_H

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

#endif //PAGE_REPLACEMENT_SIMULATOR_TABLES_H
