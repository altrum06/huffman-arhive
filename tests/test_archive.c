#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/archive/compressor.h"

// Функция сравнения файлов
int files_equal(const char* f1, const char* f2) {
    FILE* a = fopen(f1, "rb");
    FILE* b = fopen(f2, "rb");

    // Если хоть один файл не открылся - возвращаем 0
    if (a == NULL || b == NULL) {
        if (a) fclose(a);
        if (b) fclose(b);
        return 0;
    }

    int c1, c2;
    while (1) {
        c1 = fgetc(a);
        c2 = fgetc(b);

        if (c1 != c2) {
            fclose(a);
            fclose(b);
            return 0;
        }

        if (c1 == EOF) break;
    }

    fclose(a);
    fclose(b);
    return 1;
}

// Тест 1: Простой текст
void test_simple() {
    printf("Простой текст ");

    FILE* f = fopen("test.txt", "w");
    fprintf(f, "Hello World");
    fclose(f);

    assert(compress_file("test.txt", "test.bin") == 0);
    assert(decompress_file("test.bin", "output.txt") == 0);
    assert(files_equal("test.txt", "output.txt") == 1);

    printf("\n");
}

// Тест 2: Один символ
void test_one_char() {
    printf("Один символ ");

    FILE* f = fopen("one.txt", "w");
    fprintf(f, "A");
    fclose(f);

    assert(compress_file("one.txt", "one.bin") == 0);
    assert(decompress_file("one.bin", "one_out.txt") == 0);
    assert(files_equal("one.txt", "one_out.txt") == 1);

    printf("\n");
}

// Тест 3: Повторяющиеся символы
void test_repeat() {
    printf("Повторяющиеся символы ");

    FILE* f = fopen("repeat.txt", "w");
    for (int i = 0; i < 100; i++) fprintf(f, "A");
    fclose(f);

    assert(compress_file("repeat.txt", "repeat.bin") == 0);
    assert(decompress_file("repeat.bin", "repeat_out.txt") == 0);
    assert(files_equal("repeat.txt", "repeat_out.txt") == 1);

    printf("\n");
}

// Тест 4: Файл не существует
void test_error() {
    printf("Обработка ошибок ");

    assert(compress_file("notexist.txt", "out.bin") == -1);
    assert(decompress_file("notexist.bin", "out.txt") == -1);

    printf("\n");
}

// Тест 5: Русский текст
void test_russian() {
    printf("Русский текст ");

    FILE* f = fopen("russian.txt", "w");
    fprintf(f, "Привет мир");
    fclose(f);

    assert(compress_file("russian.txt", "russian.bin") == 0);
    assert(decompress_file("russian.bin", "russian_out.txt") == 0);
    assert(files_equal("russian.txt", "russian_out.txt") == 1);

    printf("\n");
}

// Запуск всех тестов
int main() {
    printf("\nТЕСТЫ АРХИВАТОРА\n");

    test_simple();
    test_one_char();
    test_repeat();
    test_error();
    test_russian();

    printf("\nВсе тесты прошли\n");

    // Очистка
    remove("test.txt"); remove("test.bin"); remove("output.txt");
    remove("one.txt"); remove("one.bin"); remove("one_out.txt");
    remove("repeat.txt"); remove("repeat.bin"); remove("repeat_out.txt");
    remove("russian.txt"); remove("russian.bin"); remove("russian_out.txt");

    return 0;
}