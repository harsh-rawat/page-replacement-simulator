#include <stdlib.h>
#include "tsearch.h"

// Add the node to the binary tree
// Returns 0 if node already exists else 1
int Put(void **root, void *data, tsearch_compare comparator) {
    void *existing;

    void *result = tsearch(data, root, comparator);
    if (result == NULL)
        TSearchError();
    else {
        existing = *(void **) result;
        if (existing != data) {
            //The value already exists in the table
            return 0;
        }
    }
    return 1;
}

//Check if the node is present in the binary tree. If not return NULL.
void *Get(void **root, void *search_node, tsearch_compare comparator) {
    void *result = tfind(search_node, root, comparator);
    if (result == NULL) {
        return NULL;
    } else {
        void *found = *(void **) result;
        return found;
    }
}

//Remove a node from the data structure
//Returns 1 if success else 0
int Remove(void **root, void *data_node, tsearch_compare comparator) {
    void *data = Get(root, data_node, comparator);
    if (data != NULL) {
        tdelete(data, root, comparator);
        return 1;
    }
    return 0;
}

void TraverseTree(void *root, tsearch_walk callback) {
    twalk(root, callback);
}

//Destroy the tree
void Destroy(void **root, tsearch_free free_method) {
//    tdestroy(root, free_method);
}