#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/queue/priority_queue.h"
#include "../src/tree/huffman_tree.h"

void test_queue_create() {
    printf("Тест создание очереди");

    PriorityQueue* pq = priority_queue_create(10);
    assert(pq != NULL);
    assert(priority_queue_is_empty(pq) == 1);
    assert(priority_queue_size(pq) == 0);

    priority_queue_free(pq);
    printf("Прошел успешно\n");
}

void test_queue_push_pop() {
    printf("Тест добавление и удаление");

    PriorityQueue* pq = priority_queue_create(10);

    HuffmanNode* a = create_node('A', 5);
    HuffmanNode* b = create_node('B', 3);

    priority_queue_push(pq, a);
    priority_queue_push(pq, b);

    assert(priority_queue_size(pq) == 2);
    assert(priority_queue_is_empty(pq) == 0);

    HuffmanNode* popped = priority_queue_pop(pq);
    assert(popped != NULL);

    priority_queue_free(pq);
    free_tree(a);
    free_tree(b);
    printf("Прошел успешно\n");
}

void test_queue_order() {
    printf("Тест правильный порядок");

    PriorityQueue* pq = priority_queue_create(10);

    HuffmanNode* a = create_node('A', 10);
    HuffmanNode* b = create_node('B', 5);
    HuffmanNode* c = create_node('C', 8);
    HuffmanNode* d = create_node('D', 1);

    priority_queue_push(pq, a);
    priority_queue_push(pq, b);
    priority_queue_push(pq, c);
    priority_queue_push(pq, d);

    //  извлекаются в порядке возрастания частот
    HuffmanNode* min1 = priority_queue_pop(pq);
    assert(min1->frequency == 1);  // D

    HuffmanNode* min2 = priority_queue_pop(pq);
    assert(min2->frequency == 5);  // B

    HuffmanNode* min3 = priority_queue_pop(pq);
    assert(min3->frequency == 8);  // C

    HuffmanNode* min4 = priority_queue_pop(pq);
    assert(min4->frequency == 10); // A

    priority_queue_free(pq);
    free_tree(a);
    free_tree(b);
    free_tree(c);
    free_tree(d);
    printf("Прошел успешно\n");
}

void queue_tests_run() {
    printf("\nТесты очереди с приорететами\n");
    test_queue_create();
    test_queue_push_pop();
    test_queue_order();
}