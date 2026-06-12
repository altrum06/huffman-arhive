#include "priority_queue.h"
#include <stdlib.h>

struct PriorityQueue{
    HuffmanNode** nodes;
    int capacity;
    int size;
};

static void change(HuffmanNode** a,HuffmanNode** b){
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->nodes[parent]->frequency <= pq->nodes[index]->frequency) {
            break;
        }
        change(&pq->nodes[parent], &pq->nodes[index]);
        index = parent;
    }
}

static void heapify_down(PriorityQueue* pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < pq->size && pq->nodes[left]->frequency < pq->nodes[smallest]->frequency) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right]->frequency < pq->nodes[smallest]->frequency) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        change(&pq->nodes[index], &pq->nodes[smallest]);
        index = smallest;
    }
}

PriorityQueue* priority_queue_create(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }

    pq->nodes = (HuffmanNode**)malloc(sizeof(HuffmanNode*) * capacity);
    if (pq->nodes == NULL) {
        free(pq);
        return NULL;
    }

    pq->capacity = capacity;
    pq->size = 0;

    return pq;
}

void priority_queue_push(PriorityQueue* pq, HuffmanNode* node) {
    if (pq == NULL || pq->size >= pq->capacity) {
        return;
    }

    int index = pq->size;
    pq->nodes[index] = node;
    pq->size++;

    heapify_up(pq, index);
}

HuffmanNode* priority_queue_pop(PriorityQueue* pq) {
    if (pq == NULL || pq->size <= 0) {
        return NULL;
    }

    HuffmanNode* result = pq->nodes[0];
    pq->size--;

    if (pq->size > 0) {
        pq->nodes[0] = pq->nodes[pq->size];
        heapify_down(pq, 0);
    }

    return result;
}

int priority_queue_is_empty(PriorityQueue* pq) {
    if (pq == NULL) {
        return 1;
    }
    return pq->size <= 0;
}

int priority_queue_size(PriorityQueue* pq) {
    if (pq == NULL) {
        return 0;
    }
    return pq->size;
}

void priority_queue_free(PriorityQueue* pq) {
    if (pq == NULL) {
        return;
    }

    if (pq->nodes != NULL) {
        free(pq->nodes);
    }

    free(pq);
}