/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#include "heap.h"

Heap *CreateHeap() {
    Heap *h = (Heap *) malloc(sizeof(Heap));
    ValidateMemoryAllocationError(h);

    h->count = 0;
    h->arr = (long *) malloc(MAX_HEAP_CAPACITY * sizeof(long));
    ValidateMemoryAllocationError(h->arr);
    h->data = (void **) malloc(MAX_HEAP_CAPACITY * sizeof(void *));
    ValidateMemoryAllocationError(h->data);

    return h;
}

void heapify_bottom_top(Heap *h, long index) {
    long temp;
    void *temp_data;
    long parent_node = (index - 1) / 2;

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

void heapify_top_bottom(Heap *h, long parent_node) {
    long left = parent_node * 2 + 1;
    long right = parent_node * 2 + 2;
    long min;
    long temp;
    void *temp_data;

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

void AddToHeap(Heap *h, long key, void *data) {
    h->arr[h->count] = key;
    h->data[h->count] = data;
    heapify_bottom_top(h, h->count);
    h->count++;
}

void *ExtractMin(Heap *h) {
    void *pop;
    if (h->count == 0) {
        return NULL;
    }

    pop = h->data[0];

    h->arr[0] = h->arr[h->count - 1];
    h->data[0] = h->data[h->count - 1];

    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

bool IsEmptyHeap(Heap *h) {
    if (h->count == 0)
        return true;

    return false;
}