#include "huffman_tree.h"
#include "../queue/priority_queue.h"
#include <stdlib.h>
#include <string.h>

HuffmanNode* create_node(unsigned char symbol, int frequency) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (node == NULL) {
        return NULL;
    }
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(HuffmanNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

HuffmanNode* build_tree(int frequencies[256]) {
    PriorityQueue* pq = priority_queue_create(256);
    if (pq == NULL) {
        return NULL;
    }

    // Создаём узлы для всех символов с ненулевой частотой
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            HuffmanNode* node = create_node((unsigned char)i, frequencies[i]);
            if (node == NULL) {
                priority_queue_free(pq);
                return NULL;
            }
            priority_queue_push(pq, node);
        }
    }

    // Если нет ни одного символа
    if (priority_queue_is_empty(pq)) {
        priority_queue_free(pq);
        return NULL;
    }

    // Строим дерево Хаффмана
    while (priority_queue_size(pq) > 1) {
        HuffmanNode* left = priority_queue_pop(pq);
        HuffmanNode* right = priority_queue_pop(pq);

        HuffmanNode* parent = create_node(0, left->frequency + right->frequency);
        if (parent == NULL) {
            free_tree(left);
            free_tree(right);
            priority_queue_free(pq);
            return NULL;
        }

        parent->left = left;
        parent->right = right;
        priority_queue_push(pq, parent);
    }

    // Извлекаем корень дерева
    HuffmanNode* root = priority_queue_pop(pq);
    priority_queue_free(pq);

    return root;  // возвращаем корень
}

void generate_codes(HuffmanNode *root, char *codes[256], int lengths[256], char *buffer, int depth) {
    if (root == NULL) {
        return;
    }

    // Если это лист (нет детей) - сохраняем код
    if (root->left == NULL && root->right == NULL) {
        // Завершаем строку нулём
        buffer[depth] = '\0';

        // Выделяем память под код символа
        codes[root->symbol] = (char*)malloc(depth + 1);
        if (codes[root->symbol] != NULL) {
            // Копируем код из буфера
            strcpy(codes[root->symbol], buffer);
            // Сохраняем длину кода
            lengths[root->symbol] = depth;
        }
        return;
    }

    // Идём налево - добавляем '0'
    if (root->left != NULL) {
        buffer[depth] = '0';
        generate_codes(root->left, codes, lengths, buffer, depth + 1);
    }

    // Идём направо - добавляем '1'
    if (root->right != NULL) {
        buffer[depth] = '1';
        generate_codes(root->right, codes, lengths, buffer, depth + 1);
    }
}