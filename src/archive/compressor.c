#include "compressor.h"
#include "../tree/huffman_tree.h"
#include "../bits/bit_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void count_frequencies(FILE *input, int frequencies[256]) {
    int byte;
    while ((byte= fgetc(input))!=EOF){
        frequencies[(unsigned char)byte]++;
    }
}


int compress_file(const char* input_file, const char* output_file) {
    FILE* input = fopen(input_file,"rb");
    if (input == NULL) {
        printf("Ошибка: не удалось открыть входной файл\n");
        return -1;
    }
    int frequencies[256]= {0};
    count_frequencies(input,frequencies);

    printf("Построение дерева...\n");
    HuffmanNode* root = build_tree(frequencies);
    if (root==NULL) {
        printf("Ошибка: build_tree вернул NULL\n");
        fclose(input);
        return -1;
    }
    printf("Дерево построено успешно\n");

    char* codes[256] = {NULL};
    int lengths[256] = {0};
    char buffer[256];
    generate_codes(root,codes, lengths,buffer,0);

    FILE* output = fopen(output_file,"wb");
    if (output == NULL) {
        fclose(input);
        free_tree(root);
        return -1;
    }

    BitWriter* bit_writer = bit_writer_create(output);

    int unique_count = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            unique_count++;
        }
    }

    bit_writer_write_int(bit_writer, unique_count);


    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            bit_writer_write_byte(bit_writer, (unsigned char)i);
            bit_writer_write_int(bit_writer, frequencies[i]);
        }
    }


    fseek(input, 0 ,SEEK_SET);

    int ch;
    while ((ch = fgetc(input))!=EOF) {
        unsigned char symbol = (unsigned char)ch;
        char* code = codes[symbol];
        if (code != NULL) {
            for (int i = 0; i < lengths[symbol]; i++) {
                bit_writer_write_bit(bit_writer, code[i] == '1');

            }
        }
    }

    bit_writer_flush(bit_writer);


    for (int i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }

    bit_writer_free(bit_writer);
    fclose(output);
    fclose(input);
    free_tree(root);
    printf("Сжатие прошло успешно: %s -> %s\n", input_file, output_file);
    return 0;
}

int decompress_file(const char* input_file, const char* output_file) {
    FILE* input = fopen(input_file,"rb");
    if(input == NULL) {
        return -1;
    }

    BitReader* bit_reader = bit_reader_create(input);
    if (bit_reader == NULL) {
        fclose(input);
        return -1;
    }

    int unique_count = bit_reader_read_int(bit_reader);
    if (unique_count <= 0) {
        bit_reader_free(bit_reader);
        fclose(input);
        return -1;
    }

    int frequencies[256] = {0};
    for (int i = 0; i< unique_count; i++) {
        int symbol = bit_reader_read_byte(bit_reader);
        int freq = bit_reader_read_int(bit_reader);
        if (symbol <0 || freq < 0) {
            bit_reader_free(bit_reader);
            fclose(input);
            return -1;
        }

        frequencies[symbol] = freq;

    }

    HuffmanNode* root = build_tree(frequencies);
    if (root == NULL) {
        bit_reader_free(bit_reader);
        fclose(input);
        return -1;
    }

    FILE* output = fopen(output_file,"wb");
    if (output == NULL) {
        bit_reader_free(bit_reader);
        fclose(input);
        free_tree(root);
        return -1;
    }

    int all_symbols= 0;
    for (int i =0; i<256; i++) {
        all_symbols += frequencies[i];
    }

    int decoded_symbols = 0;

    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < all_symbols; i++) {
            fputc(root->symbol, output);
        }
    } else {
        while (decoded_symbols < all_symbols) {
            HuffmanNode* current = root;
            while (current->left != NULL || current->right != NULL) {
                int bit = bit_reader_read_bit(bit_reader);
                if (bit == -1) {

                    bit_reader_free(bit_reader);
                    fclose(output);
                    fclose(input);
                    free_tree(root);
                    return -1;
                }
                if (bit == 0) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            fputc(current->symbol, output);
            decoded_symbols++;
        }
    }
    bit_reader_free(bit_reader);
    fclose(input);
    fclose(output);
    free_tree(root);
    printf("Распаковка прошла успешно: %s -> %s\n", input_file, output_file);
    return 0;
}