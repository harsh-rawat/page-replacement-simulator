#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_INVERTED_PAGE_TABLE_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_INVERTED_PAGE_TABLE_H

#include "tables.h"
#include "tsearch.h"
#include "fifo_page_replacement.h"

void Unlink_pf_pte(void *ipt_root, int pf_id);

void Link_pf_pte(void *ipt_root, int pf_id, page_table_entry *pte);

void Callback_free_page_frames(const void *data, VISIT order, int depth);

void *CreateInvertedPageTable(int max_pages);

#endif