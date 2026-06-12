#include <stdio.h>
#include <stdlib.h>
#include "../src/tree/huffman_tree.h"
#include <assert.h>

void test_create_node() {
    printf("Тест создание узла");

    HuffmanNode* node = create_node('A',10);
    assert(node != NULL);
    assert(node->symbol == 'A');
    assert(node->frequency == 10);
    assert(node->left == NULL);
    assert(node->right == NULL);

    free(node);
    printf("Прошел успешно\n");
}


void test_build_tree_two_symbols() {
    printf("Тест дерево из двух символов");

    int freqs[256] = {0};
    freqs['A'] = 5;
    freqs['B'] = 3;

    HuffmanNode* root = build_tree(freqs);
    assert(root != NULL);
    assert(root->left!=NULL & root->right!=NULL);

    free(root);
    printf("Прошел успешно");
}

void test_build_tree_one_symbol() {
    printf("Тест дерево из одного символа");
    int freqs[256] = {0};
    freqs['A'] = 10;

    HuffmanNode* root = build_tree(freqs);
    assert(root != NULL);

    assert(root->left == NULL & root->right == NULL);
    assert(root->symbol == 'A');
    assert(root->frequency == 10);

    free(root);
    printf("Прошел успешно");
}

void test_build_tree_empty() {
    printf("Тест пустое дерево");

    int freqs[256] = {0};
    HuffmanNode* root = build_tree(freqs);
    assert(root == NULL);
    printf("Прошел успешно");
}
void tree_tests_run() {
    printf("\nТесты дерева Хаффмана \n");
    test_create_node();
    test_build_tree_two_symbols();
    test_build_tree_one_symbol();
    test_build_tree_empty();
}