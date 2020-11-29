#include <stdlib.h>
#include "inverted_page_table.h"

page_frame *create_page_frame(int id);
int compare_memory_trace_page_frame(const void *a, const void *b);

void *CreateInvertedPageTable(int max_pages) {
    void *root = NULL;
    for (int i = 1; i <= max_pages; i++) {
        page_frame *new_page_frame = create_page_frame(i);
        Put(&root, new_page_frame,&compare_memory_trace_page_frame);
    }
    return root;
}

page_frame *create_page_frame(int id) {
    page_frame *new_page_frame = malloc(sizeof(page_frame));
    new_page_frame->ppn_id = id;
    new_page_frame->page_table_entry = NULL;
    return new_page_frame;
}

int compare_memory_trace_page_frame(const void *a, const void *b) {
    page_frame *node_a = (page_frame *) a;
    page_frame *node_b = (page_frame *) b;

    if (node_a->ppn_id < node_b->ppn_id)
        return -1;
    else if (node_a->ppn_id > node_b->ppn_id)
        return 1;
    else
        return 0;
}
