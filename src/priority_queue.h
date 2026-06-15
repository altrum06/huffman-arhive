#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffman_tree.h"

/// Очередь с приоритетом на минимальной куче (скрытая реализация в .c файле)
typedef struct PriorityQueue PriorityQueue;

/// Создать очередь с приоритетом заданной вместимости
PriorityQueue* priority_queue_create(int capacity);

/// Добавить узел в очередь (сортировка по частоте, наименьший первым)
void priority_queue_push(PriorityQueue *queue, HuffmanNode *node);

/// Извлечь узел с наименьшей частотой
HuffmanNode* priority_queue_pop(PriorityQueue *queue);

/// Проверить, пуста ли очередь
int priority_queue_is_empty(PriorityQueue *queue);

/// Получить количество элементов в очереди
int priority_queue_size(PriorityQueue *queue);

/// Освободить память очереди (сами узлы не освобождаются)
void priority_queue_free(PriorityQueue *queue);

#endif
