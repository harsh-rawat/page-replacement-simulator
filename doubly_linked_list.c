/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#include <stdlib.h>
#include "doubly_linked_list.h"

doubly_linked_list *CreateDoublyLinkedList() {
    doubly_linked_list *list = malloc(sizeof(doubly_linked_list));
    ValidateMemoryAllocationError(list);
    list->head = Create_dll_node(NULL);
    list->tail = Create_dll_node(NULL);
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->size = 0;

    return list;
}

dll_node *AddToFront(doubly_linked_list *list, void *data, int isNode) {
    if (list == NULL) return NULL;


    dll_node *new_node;
    if (isNode)
        new_node = (dll_node *) data;
    else
        new_node = Create_dll_node(data);
    //Set up the node
    new_node->next = list->head->next;
    new_node->prev = list->head;
    //Adjust other pointers
    new_node->next->prev = new_node;
    new_node->prev->next = new_node;
    list->size += 1;

    return new_node;
}

dll_node *AddToBack(doubly_linked_list *list, void *data, int isNode) {
    if (list == NULL) return NULL;

    dll_node *new_node;
    if (isNode)
        new_node = (dll_node *) data;
    else
        new_node = Create_dll_node(data);
    //Set up the node
    new_node->next = list->tail;
    new_node->prev = list->tail->prev;
    //Adjust other pointers
    new_node->next->prev = new_node;
    new_node->prev->next = new_node;
    list->size += 1;

    return new_node;
}

dll_node *DeleteFromFront(doubly_linked_list *list) {
    if (list == NULL || list->head->next == list->tail) return NULL;
    dll_node *ret_node = list->head->next;
    DeleteDLLNode(list, ret_node);
    return ret_node;
}

dll_node *DeleteFromEnd(doubly_linked_list *list) {
    if (list == NULL || list->head->next == list->tail) return NULL;
    dll_node *ret_node = list->tail->prev;
    DeleteDLLNode(list, ret_node);
    return ret_node;
}

void DeleteDLLNode(doubly_linked_list *list, dll_node *node) {
    if (node == list->head || node == list->tail) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list->size -= 1;
}

dll_node *Create_dll_node(void *data) {
    dll_node *new_node = malloc(sizeof(dll_node));
    ValidateMemoryAllocationError(new_node);
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void *GetNext(doubly_linked_list *list) {
    if (list == NULL || list->head->next == list->tail) return NULL;
    else return list->head->next->data;
}

int IsListEmpty(doubly_linked_list *list) {
    return list->head->next == list->tail ? 1 : 0;
}