// Объявления функций запуска тестов из каждого модуля
int run_tree_tests(void);
int run_queue_tests(void);
int run_bits_tests(void);
int run_codes_tests(void);
int run_archive_tests(void);

// Запустить все тесты и вернуть сумму кодов возврата
int main(void) {
    int result = 0;
    result += run_tree_tests();
    result += run_queue_tests();
    result += run_bits_tests();
    result += run_codes_tests();
    result += run_archive_tests();
    return result;
}
