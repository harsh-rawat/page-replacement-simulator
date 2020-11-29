#include <stdio.h>
#include <stdlib.h>
#include "tsearch.h"
#include "process.h"

int compare_method(const void *a, const void *b);

void free_method(void *data);

int main(int argc, char *argv[]) {
    //Parse the program arguments. If provided else consider the default ones

    process *a = malloc(sizeof(process));
    a->pid = 1;
    a->start = 0;
    a->end = 0;
    process *b = malloc(sizeof(process));
    b->pid = 1;
    b->start = 0;
    b->end = 0;

    void *root = NULL;
    Put(&root, a, &compare_method);
    Get(&root, b, &compare_method);
    Remove(&root, a, &compare_method);
    Get(&root, b, &compare_method);
    Destroy(&root, &free_method);
    return 0;
}

// This is the compare function for the binary tree
// Returns -1 if a <  b
// Returns 1  if a >  b
// Returns 0  if a == b
int compare_method(const void *a, const void *b) {
    process *node_a = (process *) a;
    process *node_b = (process *) b;

    if (node_a->pid < node_b->pid)
        return -1;
    else if (node_a->pid > node_b->pid)
        return 1;
    else
        return 0;
}

void free_method(void *data) {
    process *a = data;
    free(data);
}