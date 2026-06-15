#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <cmocka.h>
#include "../src/compressor.h"

// Сравнение двух файлов побайтово
static int files_equal(const char *f1, const char *f2) {
    FILE *a = fopen(f1, "rb");
    FILE *b = fopen(f2, "rb");
    if (a == NULL || b == NULL) {
        if (a) fclose(a);
        if (b) fclose(b);
        return 0;
    }
    int c1, c2;
    while (1) {
        c1 = fgetc(a);
        c2 = fgetc(b);
        if (c1 != c2) { fclose(a); fclose(b); return 0; }
        if (c1 == EOF) break;
    }
    fclose(a); fclose(b);
    return 1;
}

// Сжатие и распаковка простой строки "Hello World"
static void test_simple(void **state) {
    (void)state;
    FILE *f = fopen("test.txt", "w");
    assert_non_null(f);
    fprintf(f, "Hello World");
    fclose(f);

    assert_int_equal(compress_file("test.txt", "test.bin"), COMPRESS_SUCCESS);
    assert_int_equal(decompress_file("test.bin", "output.txt"), COMPRESS_SUCCESS);
    assert_true(files_equal("test.txt", "output.txt"));
}

// Сжатие и распаковка одного символа (особый случай)
static void test_one_char(void **state) {
    (void)state;
    FILE *f = fopen("one.txt", "w");
    assert_non_null(f);
    fprintf(f, "A");
    fclose(f);

    assert_int_equal(compress_file("one.txt", "one.bin"), COMPRESS_SUCCESS);
    assert_int_equal(decompress_file("one.bin", "one_out.txt"), COMPRESS_SUCCESS);
    assert_true(files_equal("one.txt", "one_out.txt"));
}

// Сжатие и распаковка 100 повторений одного символа
static void test_repeat(void **state) {
    (void)state;
    FILE *f = fopen("repeat.txt", "w");
    assert_non_null(f);
    for (int i = 0; i < 100; i++) fprintf(f, "A");
    fclose(f);

    assert_int_equal(compress_file("repeat.txt", "repeat.bin"), COMPRESS_SUCCESS);
    assert_int_equal(decompress_file("repeat.bin", "repeat_out.txt"), COMPRESS_SUCCESS);
    assert_true(files_equal("repeat.txt", "repeat_out.txt"));
}

// Проверка, что несуществующий файл возвращает ошибку
static void test_error(void **state) {
    (void)state;
    assert_int_equal(compress_file("notexist.txt", "out.bin"), COMPRESS_ERR_OPEN);
    assert_int_equal(decompress_file("notexist.bin", "out.txt"), COMPRESS_ERR_OPEN);
}

// Сжатие и распаковка русского текста "Привет мир"
static void test_russian(void **state) {
    (void)state;
    FILE *f = fopen("russian.txt", "w");
    assert_non_null(f);
    fprintf(f, "Привет мир");
    fclose(f);

    assert_int_equal(compress_file("russian.txt", "russian.bin"), COMPRESS_SUCCESS);
    assert_int_equal(decompress_file("russian.bin", "russian_out.txt"), COMPRESS_SUCCESS);
    assert_true(files_equal("russian.txt", "russian_out.txt"));
}

// Запуск всех тестов архиватора
int run_archive_tests(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_simple),
        cmocka_unit_test(test_one_char),
        cmocka_unit_test(test_repeat),
        cmocka_unit_test(test_error),
        cmocka_unit_test(test_russian),
    };
    int result = cmocka_run_group_tests(tests, NULL, NULL);
    remove("test.txt"); remove("test.bin"); remove("output.txt");
    remove("one.txt"); remove("one.bin"); remove("one_out.txt");
    remove("repeat.txt"); remove("repeat.bin"); remove("repeat_out.txt");
    remove("russian.txt"); remove("russian.bin"); remove("russian_out.txt");
    return result;
}
