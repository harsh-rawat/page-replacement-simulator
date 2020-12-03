//
// Created by Sidharth Gurbani on 11/30/20.
//

#ifndef PAGE_REPLACEMENT_SIMULATOR_HEAP_H
#define PAGE_REPLACEMENT_SIMULATOR_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_HEAP_CAPACITY 4096
struct Heap {
    int *arr;
    void **data;
    int count;
};

typedef struct Heap Heap;

Heap *CreateHeap();

void AddToHeap(Heap *h, int key, void *data);

void *ExtractMin(Heap *h);

bool IsEmptyHeap(Heap *h);

#endif //PAGE_REPLACEMENT_SIMULATOR_HEAP_H
