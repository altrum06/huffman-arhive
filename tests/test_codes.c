#include <assert.h>
#include <stdio.h>
#include "../src/tree/huffman_tree.h"

void test_codes() {
    int freqs[256] = {0};
    freqs['A'] = 5;
    freqs['B'] = 3;
    freqs['C'] = 2;

    HuffmanNode* root = build_tree(freqs);

    char* codes[256] = {NULL};
    int lengths[256] = {0};
    char buffer[256];
    generate_codes(root, codes, lengths, buffer, 0);


    assert(codes['A'] != NULL);
    assert(codes['B'] != NULL);
    assert(codes['C'] != NULL);


    assert(lengths['A'] >= 1);
    assert(lengths['B'] >= 1);
    assert(lengths['C'] >= 1);

    free_tree(root);
    printf("Проверка прошла\n");
}