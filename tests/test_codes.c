#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>
#include "../src/huffman_tree.h"

// Проверка генерации кодов Хаффмана для трёх символов
static void test_codes_generation(void **state) {
    (void)state;
    int frequencies[256] = {0};
    frequencies['A'] = 5;
    frequencies['B'] = 3;
    frequencies['C'] = 2;
    HuffmanNode *root = build_tree(frequencies);
    assert_non_null(root);

    char *codes[256] = {NULL};
    int lengths[256] = {0};
    generate_codes(root, codes, lengths);

    assert_non_null(codes['A']);
    assert_non_null(codes['B']);
    assert_non_null(codes['C']);
    assert_int_equal(lengths['A'] >= 1, 1);
    assert_int_equal(lengths['B'] >= 1, 1);
    assert_int_equal(lengths['C'] >= 1, 1);

    for (int i = 0; i < 256; i++) free(codes[i]);
    free_tree(root);
}

// Запуск всех тестов генерации кодов
int run_codes_tests(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_codes_generation),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
