/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_TABLES_H
#define PAGE_REPLACEMENT_SIMULATOR_TABLES_H

#define FIFO 1
#define LRU 2
#define CLOCK 3

#ifndef USE_MODULE
#define USE_MODULE FIFO
#endif

#if USE_MODULE == FIFO

#include "fifo_page_replacement.h"

#elif USE_MODULE == LRU
#include "fifo_page_replacement.h"
#elif USE_MODULE == CLOCK
#include "clock_page_replacement.h"
#else
#error "Invalid choice for the module to use"
#endif

#define UNUSED(x) (void)(x)

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
