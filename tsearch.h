#ifndef PAGE_REPLACEMENT_SIMULATOR_PAGE_TSEARCH_H
#define PAGE_REPLACEMENT_SIMULATOR_PAGE_TSEARCH_H

#include "error_handler.h"

#define _GNU_SOURCE

typedef int (*tsearch_compare)(const void*, const void *);
typedef void (*tsearch_free)(void*);

int Put(void **root, void *data, tsearch_compare comparator);
void *Get(void **root, void* search_node, tsearch_compare comparator);
void Remove(void **root, void* data_node, tsearch_compare comparator);
void Destroy(void **root, tsearch_free free_method);

#endif
