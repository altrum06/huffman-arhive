#ifndef EXPERIMENT_H
#define EXPERIMENT_H

// Структура для результатов  эксперимента
typedef struct {
    char name[100];
    long original_size;
    long compressed_size;
    double ratio;
    double time;
} ExperimentResult;

// Функции для экспериментов
void run_experiments();
void test_size_dependence();
void test_type_dependence();
void test_speed();


long get_file_size(const char* filename);

#endif