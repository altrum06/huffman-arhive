#include <stdio.h>

// Объявления функций из ваших тестов
void tree_tests_run();
void queue_tests_run();
void bits_tests_run();
void test_codes();
void test_archive();  // если есть отдельная функция, или main из test_archive.c

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     ЗАПУСК ВСЕХ ТЕСТОВ АРХИВАТОРА     ║\n");
    printf("╚════════════════════════════════════════╝\n");

    // Запуск всех тестов
    tree_tests_run();      // тесты дерева
    queue_tests_run();     // тесты очереди
    bits_tests_run();      // тесты битов
    test_codes();          // тесты кодов
    test_archive();        // тесты архивации

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     ✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!    ║\n");
    printf("╚════════════════════════════════════════╝\n");

    return 0;
}