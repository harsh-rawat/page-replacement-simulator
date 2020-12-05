#ifndef PAGE_REPLACEMENT_SIMULATOR_CLOCK_PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_SIMULATOR_CLOCK_PAGE_REPLACEMENT_H

#include "tsearch.h"
#include "doubly_linked_list.h"

typedef struct clock_pra {
    int max_size;
    int free_pages;
    void *node_tree;
    doubly_linked_list *cyclic_list;
} clock_pra;

typedef struct page {
    int ppn_id;
    int is_used;
    int is_in_memory;
} page;

extern clock_pra *page_replacement_algo;

clock_pra *CreateClockPRAModule(int max_size);

int GetReplacementPage(clock_pra *clock_module);

void FreePageFrame(clock_pra *clock_module, int ppn_id);

int GetOccupiedPageFrames(clock_pra *clock_module);

void UpdatePageFrameIntoMemory(clock_pra *clock_module, int ppn_id);

void UpdateAccessedPageFrame(clock_pra *clock_module, int ppn_id);

#endif
