/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_HEAP_H
#define PAGE_REPLACEMENT_SIMULATOR_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "error_handler.h"

#define MAX_HEAP_CAPACITY 4096
struct Heap {
    long *arr;
    void **data;
    long count;
};

typedef struct Heap Heap;

Heap *CreateHeap();

void AddToHeap(Heap *h, long key, void *data);

void *ExtractMin(Heap *h);

bool IsEmptyHeap(Heap *h);

#endif
