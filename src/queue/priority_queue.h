#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../tree/huffman_tree.h"

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* priority_queue_create(int capacity);
void priority_queue_push(PriorityQueue *pq, HuffmanNode *node);
HuffmanNode* priority_queue_pop(PriorityQueue *pq);
int priority_queue_is_empty(PriorityQueue *pq);
int priority_queue_size(PriorityQueue *pq);
void priority_queue_free(PriorityQueue *pq);

#endif
