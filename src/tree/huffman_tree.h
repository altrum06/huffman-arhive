#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stdlib.h>

typedef struct HuffmanNode {
    unsigned char symbol;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

HuffmanNode* create_node(unsigned char symbol, int frequency);
HuffmanNode* build_tree(int frequencies[256]);
void free_tree(HuffmanNode *root);
void generate_codes(HuffmanNode *root, char *codes[256], int lengths[256], char *buffer, int depth);

#endif