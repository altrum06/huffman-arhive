#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/priority_queue.h"
#include "../src/huffman_tree.h"

// Проверка создания очереди: не NULL, пуста, размер 0
static void test_queue_create(void **state) {
    (void)state;
    PriorityQueue *queue = priority_queue_create(10);
    assert_non_null(queue);
    assert_int_equal(priority_queue_is_empty(queue), 1);
    assert_int_equal(priority_queue_size(queue), 0);
    priority_queue_free(queue);
}

// Проверка добавления и извлечения элементов
static void test_queue_push_pop(void **state) {
    (void)state;
    PriorityQueue *queue = priority_queue_create(10);
    HuffmanNode *a = create_node('A', 5);
    HuffmanNode *b = create_node('B', 3);
    priority_queue_push(queue, a);
    priority_queue_push(queue, b);
    assert_int_equal(priority_queue_size(queue), 2);
    assert_int_equal(priority_queue_is_empty(queue), 0);
    HuffmanNode *popped = priority_queue_pop(queue);
    assert_non_null(popped);
    priority_queue_free(queue);
    free_tree(a);
    free_tree(b);
}

// Проверка порядка извлечения (min-heap: от меньшей частоты к большей)
static void test_queue_order(void **state) {
    (void)state;
    PriorityQueue *queue = priority_queue_create(10);
    HuffmanNode *a = create_node('A', 10);
    HuffmanNode *b = create_node('B', 5);
    HuffmanNode *c = create_node('C', 8);
    HuffmanNode *d = create_node('D', 1);
    priority_queue_push(queue, a);
    priority_queue_push(queue, b);
    priority_queue_push(queue, c);
    priority_queue_push(queue, d);
    assert_int_equal(huffman_node_get_frequency(priority_queue_pop(queue)), 1);
    assert_int_equal(huffman_node_get_frequency(priority_queue_pop(queue)), 5);
    assert_int_equal(huffman_node_get_frequency(priority_queue_pop(queue)), 8);
    assert_int_equal(huffman_node_get_frequency(priority_queue_pop(queue)), 10);
    priority_queue_free(queue);
    free_tree(a);
    free_tree(b);
    free_tree(c);
    free_tree(d);
}

// Запуск всех тестов очереди с приоритетом
int run_queue_tests(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_queue_create),
        cmocka_unit_test(test_queue_push_pop),
        cmocka_unit_test(test_queue_order),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
