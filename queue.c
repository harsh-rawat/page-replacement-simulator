//
// Created by Sidharth Gurbani on 11/30/20.
//

#include "queue.h"

Node *CreateNode(void *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}

Queue *CreateQueue() {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;

    return q;
}

void AddToQueue(Queue *q, void *data) {
    Node *node = CreateNode(data);

    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }

    q->rear->next = node;
    q->rear = node;
}

void RemoveFromQueue(Queue *q) {
    if (q->front == NULL)
        return;

    Node *node = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(node);
}

void *GetFromQueue(Queue *q) {
    if (q->front == NULL) return NULL;
    else return q->front->data;
}

void *GetFromQueueEnd(Queue *q) {
    if (q->front == NULL) return NULL;
    else return q->rear->data;
}

bool IsEmptyQueue(Queue *q) {
    if (q->front == NULL)
        return true;

    return false;
}