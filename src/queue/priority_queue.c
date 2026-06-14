#include "priority_queue.h"
#include <stdlib.h>

struct PriorityQueue {
    HuffmanNode** nodes;
    int capacity;
    int size;
};

// Меняем местами два указателя на узлы дерева
static void change(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Поднимаем элемент вверх по куче, если его частота меньше родительской
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

// Опускаем элемент вниз по куче, чтобы восстановить порядок после удаления
static void heapify_down(PriorityQueue* pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        // Ищем среди текущего узла и его детей узел с минимальной частотой
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

    // Выделяем память под массив указателей на узлы дерева Хаффмана
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

    // Добавляем новый узел в конец массива
    int index = pq->size;
    pq->nodes[index] = node;
    pq->size++;

    // Восстанавливаем свойство минимальной кучи
    heapify_up(pq, index);
}

HuffmanNode* priority_queue_pop(PriorityQueue* pq) {
    if (pq == NULL || pq->size <= 0) {
        return NULL;
    }

    // В минимальной куче корень содержит узел с наименьшей частотой
    HuffmanNode* result = pq->nodes[0];
    pq->size--;

    // Переносим последний элемент в корень и восстанавливаем порядок в куче
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

    // Освобождаем массив указателей
    if (pq->nodes != NULL) {
        free(pq->nodes);
    }

    // Освобождаем саму структуру очереди
    free(pq);
}

