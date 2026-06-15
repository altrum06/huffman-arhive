#include "priority_queue.h"
#include <stdlib.h>

// Внутренняя структура очереди с приоритетом на минимальной куче
struct PriorityQueue {
    HuffmanNode **nodes;
    int capacity;
    int size;
};

// Поменять местами два указателя на узлы
static void swap_pointers(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

// Восстановить свойство кучи движением вверх
static void heapify_up(PriorityQueue *queue, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (huffman_node_get_frequency(queue->nodes[parent]) <= huffman_node_get_frequency(queue->nodes[index])) {
            break;
        }
        swap_pointers(&queue->nodes[parent], &queue->nodes[index]);
        index = parent;
    }
}

// Восстановить свойство кучи движением вниз
static void heapify_down(PriorityQueue *queue, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < queue->size && huffman_node_get_frequency(queue->nodes[left]) < huffman_node_get_frequency(queue->nodes[smallest])) {
            smallest = left;
        }
        if (right < queue->size && huffman_node_get_frequency(queue->nodes[right]) < huffman_node_get_frequency(queue->nodes[smallest])) {
            smallest = right;
        }
        if (smallest == index) break;
        swap_pointers(&queue->nodes[index], &queue->nodes[smallest]);
        index = smallest;
    }
}

// Создать очередь с приоритетом заданной вместимости
PriorityQueue* priority_queue_create(int capacity) {
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    if (queue == NULL) return NULL;

    queue->nodes = malloc(sizeof(HuffmanNode *) * capacity);
    if (queue->nodes == NULL) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

// Добавить новый узел в очередь
void priority_queue_push(PriorityQueue *queue, HuffmanNode *node) {
    if (queue == NULL || queue->size >= queue->capacity) return;
    int index = queue->size;
    queue->nodes[index] = node;
    queue->size++;
    heapify_up(queue, index);
}

// Извлечь узел с минимальной частотой
HuffmanNode* priority_queue_pop(PriorityQueue *queue) {
    if (queue == NULL || queue->size <= 0) return NULL;
    HuffmanNode *result = queue->nodes[0];
    queue->size--;
    if (queue->size > 0) {
        queue->nodes[0] = queue->nodes[queue->size];
        heapify_down(queue, 0);
    }
    return result;
}

// Проверить, пуста ли очередь
int priority_queue_is_empty(PriorityQueue *queue) {
    return queue == NULL || queue->size <= 0;
}

// Получить количество элементов в очереди
int priority_queue_size(PriorityQueue *queue) {
    return queue == NULL ? 0 : queue->size;
}

// Освободить память очереди (узлы не освобождаются)
void priority_queue_free(PriorityQueue *queue) {
    if (queue == NULL) return;
    free(queue->nodes);
    free(queue);
}
