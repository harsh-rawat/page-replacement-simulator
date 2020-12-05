#include <stdlib.h>
#include "fifo_page_replacement.h"

page *create_page(int index);

void initialize_free_list(fifo_module *fifo, int max_size);

int compare_dll_ppn(const void *a, const void *b);

dll_node *get_referenced_node(fifo_module *fifo, int ppn_id);

fifo_module *CreateFIFOModule(int max_size) {
    fifo_module *fifo = malloc(sizeof(fifo_module));
    initialize_free_list(fifo, max_size);
    fifo->fifo_list = CreateDoublyLinkedList();
    fifo->max_size = max_size;
    fifo->free_pages = max_size;
    return fifo;
}

int GetReplacementPage(fifo_module *fifo) {
    dll_node *free_node;
    if (!IsListEmpty(fifo->free_list)) {
        free_node = DeleteFromFront(fifo->free_list);
    } else {
        free_node = DeleteFromFront(fifo->fifo_list);
    }
    page *replacement = (page *) free_node->data;
    AddToBack(fifo->fifo_list, free_node, 1);

    return replacement->ppn_id;
}

void UpdatePageFrameIntoMemory(fifo_module *fifo, int ppn_id) {
    dll_node *curr_node = get_referenced_node(fifo, ppn_id);
    if (curr_node == NULL) return;

    page *reference_page = (page *) curr_node->data;
    if (reference_page->is_free) {
        reference_page->is_free = 0;
        fifo->free_pages -= 1;
    }
}

void FreePageFrame(fifo_module *fifo, int ppn_id) {
    dll_node *curr_node = get_referenced_node(fifo, ppn_id);
    if (curr_node == NULL) return;

    page *reference_page = (page *) curr_node->data;
    if (!reference_page->is_free) {
        reference_page->is_free = 1;
        fifo->free_pages += 1;
        DeleteDLLNode(fifo->fifo_list, curr_node);
        AddToBack(fifo->free_list, curr_node, 1);
    }
}

int GetOccupiedPageFrames(fifo_module *fifo) {
    return (fifo->max_size - fifo->free_pages);
}

#if USE_MODULE == LRU

void UpdateAccessedPageFrame(fifo_module *fifo, int ppn_id) {
    dll_node *curr_node = get_referenced_node(fifo, ppn_id);
    if (curr_node == NULL) return;

    page *reference_page = (page *) curr_node->data;
    if (!reference_page->is_free) {
        DeleteDLLNode(fifo->fifo_list, curr_node);
        AddToBack(fifo->fifo_list, curr_node, 1);
    }
}

#else
void UpdateAccessedPageFrame(fifo_module* fifo, int ppn_id){
    return;
}
#endif

dll_node *get_referenced_node(fifo_module *fifo, int ppn_id) {
    page *reference_page = create_page(ppn_id);
    dll_node *reference_node = Create_dll_node(reference_page);
    dll_node *curr_node = Get(&fifo->node_tree, reference_node, &compare_dll_ppn);
    free(reference_page);
    free(reference_node);

    if (curr_node == NULL) return NULL;
    else return curr_node;
}

void initialize_free_list(fifo_module *fifo, int max_size) {
    doubly_linked_list *free_list = CreateDoublyLinkedList();
    fifo->free_list = free_list;
    fifo->node_tree = NULL;

    page *curr_page;
    dll_node *curr_node;
    for (int index = 1; index <= max_size; index++) {
        curr_page = create_page(index);
        curr_node = AddToBack(free_list, curr_page, 0);
        Put(&fifo->node_tree, curr_node, &compare_dll_ppn);
    }
}

int compare_dll_ppn(const void *a, const void *b) {
    page *node_a = (page *) ((dll_node *) a)->data;
    page *node_b = (page *) ((dll_node *) b)->data;

    if (node_a->ppn_id < node_b->ppn_id)
        return -1;
    else if (node_a->ppn_id > node_b->ppn_id)
        return 1;
    else
        return 0;
}

page *create_page(int index) {
    page *curr_page = malloc(sizeof(page));
    curr_page->ppn_id = index;
    curr_page->is_free = 1;
    return curr_page;
}