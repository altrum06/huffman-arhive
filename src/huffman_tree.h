#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

/// Узел дерева Хаффмана (скрытая реализация в .c файле)
typedef struct HuffmanNode HuffmanNode;

/// Создать новый лист дерева с символом и его частотой
HuffmanNode* create_node(unsigned char symbol, int frequency);

/// Построить дерево Хаффмана по таблице частот (массив на 256 элементов)
HuffmanNode* build_tree(int frequencies[256]);

/// Рекурсивно освободить память всего дерева
void free_tree(HuffmanNode *root);

/// Сгенерировать коды Хаффмана для каждого листа дерева
void generate_codes(HuffmanNode *root, char *codes[256], int lengths[256]);

/// Получить символ, хранящийся в узле
unsigned char huffman_node_get_symbol(const HuffmanNode *node);

/// Получить частоту символа в узле
int huffman_node_get_frequency(const HuffmanNode *node);

/// Проверить, является ли узел листом (нет детей)
int huffman_node_is_leaf(const HuffmanNode *node);

/// Получить левого потомка узла
HuffmanNode* huffman_node_get_left(HuffmanNode *node);

/// Получить правого потомка узла
HuffmanNode* huffman_node_get_right(HuffmanNode *node);

#endif
