#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/tree/huffman_tree.h"

// Проверяем создание одного узла дерева
void test_create_node() {
    printf("Тест создание узла\n");

    HuffmanNode* node = create_node('A', 10);

    // Проверяем, что узел создан и поля заполнены правильно
    assert(node != NULL);
    assert(node->symbol == 'A');
    assert(node->frequency == 10);
    assert(node->left == NULL);
    assert(node->right == NULL);

    free(node);

    printf("Прошел успешно\n");
}

// Проверяем построение дерева из двух разных символов
void test_build_tree_two_symbols() {
    printf("Тест дерево из двух символов\n");

    int freqs[256] = {0};
    freqs['A'] = 5;
    freqs['B'] = 3;

    HuffmanNode* root = build_tree(freqs);

    // У дерева из двух символов должен быть корень и два дочерних узла
    assert(root != NULL);
    assert(root->left != NULL && root->right != NULL);

    free_tree(root);

    printf("Прошел успешно\n");
}

// Проверяем случай, когда в файле есть только один уникальный символ
void test_build_tree_one_symbol() {
    printf("Тест дерево из одного символа\n");

    int freqs[256] = {0};
    freqs['A'] = 10;

    HuffmanNode* root = build_tree(freqs);

    // В этом случае дерево состоит только из одного узла
    assert(root != NULL);
    assert(root->left == NULL && root->right == NULL);
    assert(root->symbol == 'A');
    assert(root->frequency == 10);

    free_tree(root);

    printf("Прошел успешно\n");
}

// Проверяем случай пустого файла, когда частот нет
void test_build_tree_empty() {
    printf("Тест пустое дерево\n");

    int freqs[256] = {0};
    HuffmanNode* root = build_tree(freqs);

    // Для пустого набора частот дерево построить нельзя
    assert(root == NULL);

    printf("Прошел успешно\n");
}

// Запускаем все тесты для дерева Хаффмана
void tree_tests_run() {
    printf("\nТесты дерева Хаффмана\n");

    test_create_node();
    test_build_tree_two_symbols();
    test_build_tree_one_symbol();
    test_build_tree_empty();
}

