/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_LINKED_LIST_H
#define PAGE_REPLACEMENT_SIMULATOR_LINKED_LIST_H

#include "error_handler.h"

struct list_node {
    //data stored in the node
    void *data;
    //pointer to next node of the list
    struct list_node *next;
};

typedef struct list_node list_node;

list_node *CreateLinkedList();

void AddNode(list_node *head, void *data);

void *GetNext(list_node *node);

int Contains(list_node *head, void *data);

void DeleteNode(list_node *head, list_node *node);

void DeleteLinkedList(list_node *head);

int GetLength(list_node *head);

#endif
