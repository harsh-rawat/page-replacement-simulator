#ifndef PAGE_REPLACEMENT_SIMULATOR_DOUBLY_LINKED_LIST_H
#define PAGE_REPLACEMENT_SIMULATOR_DOUBLY_LINKED_LIST_H

struct dll_node {
    void *data;
    struct dll_node *next;
    struct dll_node *prev;
};

typedef struct dll_node dll_node;

typedef struct doubly_linked_list {
    int size;
    dll_node *head;
    dll_node *tail;
} doubly_linked_list;

dll_node *Create_dll_node(void *data);

doubly_linked_list *CreateDoublyLinkedList();

dll_node *AddToFront(doubly_linked_list *list, void *data, int isNode);

dll_node *AddToBack(doubly_linked_list *list, void *data, int isNode);

int GetSize(doubly_linked_list *list);

void DeleteDLLNode(doubly_linked_list *list, dll_node *node);

dll_node *DeleteFromFront(doubly_linked_list *list);

dll_node *DeleteFromEnd(doubly_linked_list *list);

void *GetNext(doubly_linked_list *list);

#endif
