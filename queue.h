/**
 * @author Harsh Rawat, harsh-rawat, hrawat2
 * @author Sidharth Gurbani, gurbani, gurbani
 */

#ifndef PAGE_REPLACEMENT_SIMULATOR_QUEUE_H
#define PAGE_REPLACEMENT_SIMULATOR_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "error_handler.h"

struct Node {
    void *data;
    struct Node *next;
};

struct Queue {
    struct Node *front;
    struct Node *rear;
};

typedef struct Queue Queue;
typedef struct Node Node;

Queue *CreateQueue();

void AddToQueue(Queue *q, void *data);

void RemoveFromQueue(Queue *q);

void *GetFromQueue(Queue *q);

void *GetFromQueueEnd(Queue *q);

bool IsEmptyQueue(Queue *q);

#endif //PAGE_REPLACEMENT_SIMULATOR_QUEUE_H
