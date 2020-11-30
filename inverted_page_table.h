#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_INVERTED_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_INVERTED_PAGE_TABLE_H

#include "page_table.h"

typedef struct page_frame {
    int ppn_id;
    page_table_entry *page_table_entry;
} page_frame;

void Unlink_pf_pte(void *ipt_root, int pf_id);

void Link_pf_pte(void *ipt_root, int pf_id, page_table_entry *pte)

#endif
