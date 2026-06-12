#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../src/bits/bit_io.h"


void test_bit_write_read() {
    printf("Тест запись и чтение битов");

    FILE* f = fopen("test_bits.txt", "wb");
    BitWriter* bw = bit_writer_create(f);

    bit_writer_write_bit(bw, 1);
    bit_writer_write_bit(bw, 0);
    bit_writer_write_bit(bw, 1);
    bit_writer_write_bit(bw, 1);

    bit_writer_flush(bw);
    bit_writer_free(bw);
    fclose(f);

    f = fopen("test_bits.bin", "rb");
    BitReader* br = bit_reader_create(f);

    int b1 = bit_reader_read_bit(br);
    int b2 = bit_reader_read_bit(br);
    int b3 = bit_reader_read_bit(br);
    int b4 = bit_reader_read_bit(br);

    assert(b1 == 1);
    assert(b2 == 0);
    assert(b3 == 1);
    assert(b4 == 1);

    bit_reader_free(br);
    fclose(f);

    remove("test_bits.bin");
    printf("Прошел успешно\n");
}

void test_byte_write_read() {
    printf("Тест запись и чтение байта");

    FILE* f = fopen("test_byte.bin", "wb");
    BitWriter* bw = bit_writer_create(f);

    bit_writer_write_byte(bw, 0xAB);
    bit_writer_flush(bw);
    bit_writer_free(bw);
    fclose(f);

    f = fopen("test_byte.bin", "rb");
    BitReader* br = bit_reader_create(f);

    int byte = bit_reader_read_byte(br);
    assert(byte == 0xAB);

    bit_reader_free(br);
    fclose(f);

    remove("test_byte.bin");
    printf("Прошел проверку\n");
}

void test_int_write_read() {
    printf("Тест запись и чтение целого числа");

    FILE* f = fopen("test_int.bin", "wb");
    BitWriter* bw = bit_writer_create(f);

    bit_writer_write_int(bw, 10000);
    bit_writer_flush(bw);
    bit_writer_free(bw);
    fclose(f);

    f = fopen("test_int.bin", "rb");
    BitReader* br = bit_reader_create(f);

    int value = bit_reader_read_int(br);
    assert(value == 10000);

    bit_reader_free(br);
    fclose(f);

    remove("test_int.bin");
    printf("Прошел успешно\n");
}

void bits_tests_run() {
    printf("\nТесты битовых операций \n");
    test_bit_write_read();
    test_byte_write_read();
    test_int_write_read();
}













