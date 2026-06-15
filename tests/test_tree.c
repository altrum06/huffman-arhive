#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/huffman_tree.h"

// Проверка создания узла и аксессоров
static void test_create_node(void **state) {
    (void)state;
    HuffmanNode *node = create_node('A', 10);
    assert_non_null(node);
    assert_int_equal(huffman_node_get_symbol(node), 'A');
    assert_int_equal(huffman_node_get_frequency(node), 10);
    assert_int_equal(huffman_node_is_leaf(node), 1);
    free_tree(node);
}

// Проверка построения дерева из двух символов
static void test_build_tree_two_symbols(void **state) {
    (void)state;
    int frequencies[256] = {0};
    frequencies['A'] = 5;
    frequencies['B'] = 3;
    HuffmanNode *root = build_tree(frequencies);
    assert_non_null(root);
    assert_int_equal(huffman_node_is_leaf(root), 0);
    assert_non_null(huffman_node_get_left(root));
    assert_non_null(huffman_node_get_right(root));
    free_tree(root);
}

// Проверка дерева из одного символа (особый случай)
static void test_build_tree_one_symbol(void **state) {
    (void)state;
    int frequencies[256] = {0};
    frequencies['A'] = 10;
    HuffmanNode *root = build_tree(frequencies);
    assert_non_null(root);
    assert_int_equal(huffman_node_is_leaf(root), 1);
    assert_int_equal(huffman_node_get_symbol(root), 'A');
    assert_int_equal(huffman_node_get_frequency(root), 10);
    free_tree(root);
}

// Проверка, что пустая таблица частот возвращает NULL
static void test_build_tree_empty(void **state) {
    (void)state;
    int frequencies[256] = {0};
    HuffmanNode *root = build_tree(frequencies);
    assert_null(root);
}

// Запуск всех тестов дерева Хаффмана
int run_tree_tests(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_node),
        cmocka_unit_test(test_build_tree_two_symbols),
        cmocka_unit_test(test_build_tree_one_symbol),
        cmocka_unit_test(test_build_tree_empty),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
