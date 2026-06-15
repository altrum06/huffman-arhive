#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <cmocka.h>
#include "../src/bit_io.h"

// Проверка записи и чтения отдельных битов
static void test_bit_write_read(void **state) {
    (void)state;
    FILE *f = fopen("test_bits.bin", "wb");
    assert_non_null(f);
    BitWriter *writer = bit_writer_create(f);
    assert_non_null(writer);
    bit_writer_write_bit(writer, 1);
    bit_writer_write_bit(writer, 0);
    bit_writer_write_bit(writer, 1);
    bit_writer_write_bit(writer, 1);
    bit_writer_flush(writer);
    bit_writer_free(writer);
    fclose(f);

    f = fopen("test_bits.bin", "rb");
    assert_non_null(f);
    BitReader *reader = bit_reader_create(f);
    assert_non_null(reader);
    assert_int_equal(bit_reader_read_bit(reader), 1);
    assert_int_equal(bit_reader_read_bit(reader), 0);
    assert_int_equal(bit_reader_read_bit(reader), 1);
    assert_int_equal(bit_reader_read_bit(reader), 1);
    bit_reader_free(reader);
    fclose(f);
    remove("test_bits.bin");
}

// Проверка записи и чтения байта (0xAB)
static void test_byte_write_read(void **state) {
    (void)state;
    FILE *f = fopen("test_byte.bin", "wb");
    assert_non_null(f);
    BitWriter *writer = bit_writer_create(f);
    assert_non_null(writer);
    bit_writer_write_byte(writer, 0xAB);
    bit_writer_flush(writer);
    bit_writer_free(writer);
    fclose(f);

    f = fopen("test_byte.bin", "rb");
    assert_non_null(f);
    BitReader *reader = bit_reader_create(f);
    assert_non_null(reader);
    assert_int_equal(bit_reader_read_byte(reader), 0xAB);
    bit_reader_free(reader);
    fclose(f);
    remove("test_byte.bin");
}

// Проверка записи и чтения 32-битного целого (10000)
static void test_int_write_read(void **state) {
    (void)state;
    FILE *f = fopen("test_int.bin", "wb");
    assert_non_null(f);
    BitWriter *writer = bit_writer_create(f);
    assert_non_null(writer);
    bit_writer_write_int(writer, 10000);
    bit_writer_flush(writer);
    bit_writer_free(writer);
    fclose(f);

    f = fopen("test_int.bin", "rb");
    assert_non_null(f);
    BitReader *reader = bit_reader_create(f);
    assert_non_null(reader);
    assert_int_equal(bit_reader_read_int(reader), 10000);
    bit_reader_free(reader);
    fclose(f);
    remove("test_int.bin");
}

// Запуск всех тестов побитового ввода-вывода
int run_bits_tests(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bit_write_read),
        cmocka_unit_test(test_byte_write_read),
        cmocka_unit_test(test_int_write_read),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
