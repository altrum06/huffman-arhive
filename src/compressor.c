#include "compressor.h"
#include "huffman_tree.h"
#include "bit_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Подсчитать частоты всех байтов во входном файле
static void count_frequencies(FILE *input, int frequencies[256]) {
    int byte;
    while ((byte = fgetc(input)) != EOF) {
        frequencies[(unsigned char)byte]++;
    }
}

// Сжать файл: подсчёт частот -> дерево -> заголовок -> кодирование
int compress_file(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "rb");
    if (input == NULL) return COMPRESS_ERR_OPEN;

    int frequencies[256] = {0};
    count_frequencies(input, frequencies);

    HuffmanNode *root = build_tree(frequencies);
    if (root == NULL) {
        fclose(input);
        return COMPRESS_ERR_MEM;
    }

    char *codes[256] = {NULL};
    int lengths[256] = {0};
    generate_codes(root, codes, lengths);

    FILE *output = fopen(output_file, "wb");
    if (output == NULL) {
        fclose(input);
        free_tree(root);
        return COMPRESS_ERR_OPEN;
    }

    BitWriter *writer = bit_writer_create(output);
    if (writer == NULL) {
        fclose(input);
        fclose(output);
        free_tree(root);
        return COMPRESS_ERR_MEM;
    }

    // Подсчёт и запись заголовка: количество уникальных символов и их частоты
    int unique_count = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) unique_count++;
    }

    bit_writer_write_int(writer, unique_count);
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            bit_writer_write_byte(writer, (unsigned char)i);
            bit_writer_write_int(writer, frequencies[i]);
        }
    }

    // Второй проход: замена каждого символа его кодом Хаффмана
    fseek(input, 0, SEEK_SET);
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        unsigned char symbol = (unsigned char)ch;
        char *code = codes[symbol];
        if (code != NULL) {
            for (int i = 0; i < lengths[symbol]; i++) {
                bit_writer_write_bit(writer, code[i] == '1');
            }
        }
    }

    bit_writer_flush(writer);

    // Очистка памяти
    for (int i = 0; i < 256; i++) free(codes[i]);
    bit_writer_free(writer);
    fclose(output);
    fclose(input);
    free_tree(root);
    return COMPRESS_SUCCESS;
}

// Распаковать файл: заголовок -> дерево -> декодирование
int decompress_file(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "rb");
    if (input == NULL) return COMPRESS_ERR_OPEN;

    BitReader *reader = bit_reader_create(input);
    if (reader == NULL) {
        fclose(input);
        return COMPRESS_ERR_MEM;
    }

    // Чтение заголовка: количество символов и таблица частот
    int unique_count = bit_reader_read_int(reader);
    if (unique_count <= 0) {
        bit_reader_free(reader);
        fclose(input);
        return COMPRESS_ERR_DATA;
    }

    int frequencies[256] = {0};
    for (int i = 0; i < unique_count; i++) {
        int symbol = bit_reader_read_byte(reader);
        int frequency = bit_reader_read_int(reader);
        if (symbol < 0 || frequency < 0) {
            bit_reader_free(reader);
            fclose(input);
            return COMPRESS_ERR_DATA;
        }
        frequencies[symbol] = frequency;
    }

    // Восстановление дерева Хаффмана
    HuffmanNode *root = build_tree(frequencies);
    if (root == NULL) {
        bit_reader_free(reader);
        fclose(input);
        return COMPRESS_ERR_MEM;
    }

    FILE *output = fopen(output_file, "wb");
    if (output == NULL) {
        bit_reader_free(reader);
        fclose(input);
        free_tree(root);
        return COMPRESS_ERR_OPEN;
    }

    // Общее количество символов в исходном файле
    int all_symbols = 0;
    for (int i = 0; i < 256; i++) all_symbols += frequencies[i];

    // Если дерево состоит из одного листа — особый случай
    if (huffman_node_is_leaf(root)) {
        unsigned char symbol = huffman_node_get_symbol(root);
        for (int i = 0; i < all_symbols; i++) fputc(symbol, output);
    } else {
        // Иначе: чтение битов и спуск по дереву до листа
        int decoded = 0;
        while (decoded < all_symbols) {
            HuffmanNode *current = root;
            while (!huffman_node_is_leaf(current)) {
                int bit = bit_reader_read_bit(reader);
                if (bit == -1) {
                    bit_reader_free(reader);
                    fclose(output);
                    fclose(input);
                    free_tree(root);
                    return COMPRESS_ERR_READ;
                }
                current = bit ? huffman_node_get_right(current) : huffman_node_get_left(current);
            }
            fputc(huffman_node_get_symbol(current), output);
            decoded++;
        }
    }

    bit_reader_free(reader);
    fclose(input);
    fclose(output);
    free_tree(root);
    return COMPRESS_SUCCESS;
}
