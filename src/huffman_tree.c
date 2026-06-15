#include "huffman_tree.h"
#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>

// Внутренняя структура узла дерева Хаффмана
struct HuffmanNode {
    unsigned char symbol;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

// Создать новый лист с заданным символом и частотой
HuffmanNode* create_node(unsigned char symbol, int frequency) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (node == NULL) return NULL;
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Рекурсивно освободить все узлы дерева
void free_tree(HuffmanNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Внутренняя рекурсивная функция построения кодов Хаффмана
// buffer — временный массив для накопления строки кода, depth — текущая глубина
static void generate_codes_recursive(HuffmanNode *root, char *codes[256], int lengths[256], char *buffer, int depth) {
    if (root == NULL) return;
    // Лист дерева — сохраняем накопленный код
    if (root->left == NULL && root->right == NULL) {
        buffer[depth] = '\0';
        codes[root->symbol] = malloc(depth + 1);
        if (codes[root->symbol] != NULL) {
            strcpy(codes[root->symbol], buffer);
            lengths[root->symbol] = depth;
        }
        return;
    }
    // Движение влево — добавляем '0' к коду
    if (root->left != NULL) {
        buffer[depth] = '0';
        generate_codes_recursive(root->left, codes, lengths, buffer, depth + 1);
    }
    // Движение вправо — добавляем '1' к коду
    if (root->right != NULL) {
        buffer[depth] = '1';
        generate_codes_recursive(root->right, codes, lengths, buffer, depth + 1);
    }
}

// Сгенерировать коды Хаффмана для всех листьев дерева
void generate_codes(HuffmanNode *root, char *codes[256], int lengths[256]) {
    char buffer[256];
    generate_codes_recursive(root, codes, lengths, buffer, 0);
}

// Построить дерево Хаффмана по таблице частот
HuffmanNode* build_tree(int frequencies[256]) {
    PriorityQueue *queue = priority_queue_create(256);
    if (queue == NULL) return NULL;

    // Создаём листья для всех символов с ненулевой частотой
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            HuffmanNode *node = create_node((unsigned char)i, frequencies[i]);
            if (node == NULL) {
                priority_queue_free(queue);
                return NULL;
            }
            priority_queue_push(queue, node);
        }
    }

    // Если нет ни одного символа — дерево построить нельзя
    if (priority_queue_is_empty(queue)) {
        priority_queue_free(queue);
        return NULL;
    }

    // Последовательно объединяем два узла с наименьшими частотами
    while (priority_queue_size(queue) > 1) {
        HuffmanNode *left = priority_queue_pop(queue);
        HuffmanNode *right = priority_queue_pop(queue);
        HuffmanNode *parent = create_node(0, left->frequency + right->frequency);
        if (parent == NULL) {
            free_tree(left);
            free_tree(right);
            priority_queue_free(queue);
            return NULL;
        }
        parent->left = left;
        parent->right = right;
        priority_queue_push(queue, parent);
    }

    // Последний оставшийся узел — корень дерева
    HuffmanNode *root = priority_queue_pop(queue);
    priority_queue_free(queue);
    return root;
}

// Получить символ узла
unsigned char huffman_node_get_symbol(const HuffmanNode *node) {
    return node->symbol;
}

// Получить частоту узла
int huffman_node_get_frequency(const HuffmanNode *node) {
    return node->frequency;
}

// Проверить, является ли узел листом
int huffman_node_is_leaf(const HuffmanNode *node) {
    return node->left == NULL && node->right == NULL;
}

// Получить левого потомка
HuffmanNode* huffman_node_get_left(HuffmanNode *node) {
    return node->left;
}

// Получить правого потомка
HuffmanNode* huffman_node_get_right(HuffmanNode *node) {
    return node->right;
}
