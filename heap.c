//
// Created by Sidharth Gurbani on 11/30/20.
//
#include "heap.h"

Heap* CreateHeap() {
    Heap* h = (Heap*) malloc(sizeof(Heap));

    if (h==NULL) {
        // Throw error as in error_handler.c
        exit(EXIT_FAILURE);
    }
    h->count = 0;
    h->arr = (int* ) malloc(MAX_HEAP_CAPACITY*sizeof(int));
    h->data = (void**) malloc(MAX_HEAP_CAPACITY*sizeof(void*));

    if (h->arr==NULL || h->data==NULL) {
        // Throw error as in error_handler.c
        exit(EXIT_FAILURE);
    }

    return h;
}

void heapify_bottom_top(Heap* h, int index) {
    int temp;
    void* temp_data;
    int parent_node = (index-1)/2;

    if (h->arr[parent_node] > h->arr[index]) {
        temp = h->arr[parent_node];
        temp_data = h->data[parent_node];

        h->arr[parent_node] = h->arr[index];
        h->data[parent_node] = h->data[index];

        h->arr[index] = temp;
        h->data[index] = temp_data;

        heapify_bottom_top(h, parent_node);
    }
}

void heapify_top_bottom(Heap* h, int parent_node) {
    int left = parent_node*2 + 1;
    int right = parent_node*2 + 2;
    int min;
    int temp;
    void* temp_data;

    if (left >= h->count || left < 0)
        left = -1;

    if (right >= h->count || right < 0)
        right = -1;

    if (left != -1 && h->arr[left] < h->arr[parent_node])
        min = left;
    else
        min = parent_node;

    if (right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if (min != parent_node) {
        temp = h->arr[min];
        temp_data = h->data[min];

        h->arr[min] = h->arr[parent_node];
        h->data[min] = h->data[parent_node];

        h->arr[parent_node] = temp;
        h->data[parent_node] = temp_data;

        heapify_top_bottom(h, min);
    }
}

void AddToHeap(Heap* h, int key, void* data) {
    h->arr[h->count] = key;
    h->data[h->count] = data;
    heapify_bottom_top(h, h->count);
    h->count++;
}

void* ExtractMin(Heap* h) {
    void* pop;
    if (h->count==0) {
        return NULL;
    }

    pop = h->data[0];

    h->arr[0] = h->arr[h->count - 1];
    h->data[0] = h->data[h->count - 1];

    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

bool IsEmptyHeap(Heap* h) {
    if (h->count == 0)
        return true;

    return false;
}