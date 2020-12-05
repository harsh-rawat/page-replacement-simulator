#include <stdlib.h>
#include "clock_page_replacement.h"

dll_node *get_node_from_tree(clock_pra *clock_module, int ppn_id);

page *create_clock_page(int index);

int compare_dll_ppn(const void *a, const void *b);

void initialize_cyclic_list(clock_pra *clock_pra, int max_size);

clock_pra *CreateClockPRAModule(int max_size) {
    clock_pra *clock_module = malloc(sizeof(clock_module));
    clock_module->max_size = max_size;
    clock_module->free_pages = max_size;
    initialize_cyclic_list(clock_module, max_size);
    return clock_module;
}

int GetReplacementPage(clock_pra *clock_module) {
    dll_node *curr_node;
    page *curr_page;
    while (1) {
        curr_node = DeleteFromFront(clock_module->cyclic_list);
        curr_page = curr_node->data;
        if (curr_page->is_used) {
            curr_page->is_used = 0;
            AddToBack(clock_module->cyclic_list, curr_node, 1);
        } else {
            curr_page->is_used = 1;
            AddToBack(clock_module->cyclic_list, curr_node, 1);
            break;
        }
    }

    return curr_page->ppn_id;
}

void UpdateAccessedPageFrame(clock_pra *clock_module, int ppn_id) {
    dll_node *curr_node = get_node_from_tree(clock_module, ppn_id);
    if (curr_node == NULL) return;

    page *accessed_page = curr_node->data;
    accessed_page->is_used = 1;
}

void UpdatePageFrameIntoMemory(clock_pra *clock_module, int ppn_id) {
    dll_node *curr_node = get_node_from_tree(clock_module, ppn_id);
    if (curr_node == NULL) return;

    page *accessed_page = curr_node->data;
    if (!accessed_page->is_in_memory) {
        accessed_page->is_in_memory = 1;
        clock_module->free_pages -= 1;
    }
}

int GetOccupiedPageFrames(clock_pra *clock_module) {
    return (clock_module->max_size - clock_module->free_pages);
}

void FreePageFrame(clock_pra *clock_module, int ppn_id) {
    dll_node *curr_node = get_node_from_tree(clock_module, ppn_id);
    if (curr_node == NULL) return;

    page *accessed_page = curr_node->data;
    if (accessed_page->is_in_memory) {
        accessed_page->is_in_memory = 0;
        clock_module->free_pages += 1;
    }
}

dll_node *get_node_from_tree(clock_pra *clock_module, int ppn_id) {
    page *reference_page = create_clock_page(ppn_id);
    dll_node *reference_node = Create_dll_node(reference_page);
    dll_node *curr_node = Get(&clock_module->node_tree, reference_node, &compare_dll_ppn);
    free(reference_page);
    free(reference_node);

    if (curr_node == NULL) return NULL;
    else return curr_node;
}

void initialize_cyclic_list(clock_pra *clock_pra, int max_size) {
    doubly_linked_list *cyclic_list = CreateDoublyLinkedList();
    clock_pra->cyclic_list = cyclic_list;
    clock_pra->node_tree = NULL;

    page *curr_page;
    dll_node *curr_node;
    for (int index = 1; index <= max_size; index++) {
        curr_page = create_clock_page(index);
        curr_node = AddToBack(cyclic_list, curr_page, 0);
        Put(&clock_pra->node_tree, curr_node, &compare_dll_ppn);
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

page *create_clock_page(int index) {
    page *new_page = malloc(sizeof(page));
    new_page->ppn_id = index;
    new_page->is_in_memory = 0;
    new_page->is_used = 0;
    return new_page;
}