# Архиватор на базе алгоритма Хаффмана

[![CI](https://github.com/altrum06/huffman-arhive/actions/workflows/ci.yml/badge.svg)](https://github.com/altrum06/huffman-arhive/actions/workflows/ci.yml)
[![Lint](https://github.com/altrum06/huffman-arhive/actions/workflows/lint.yml/badge.svg)](https://github.com/altrum06/huffman-arhive/actions/workflows/lint.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Консольное приложение на языке C для сжатия и восстановления файлов без потерь.

## Алгоритм

В основе программы лежит **алгоритм Хаффмана** — метод сжатия без потерь, строящий оптимальные префиксные коды. Частые символы кодируются короткими битовыми последовательностями, редкие — длинными.

## Структура проекта

```
huffman-arhive/
├── .github/workflows/
│   ├── ci.yml             # CI: Linux + Windows
│   └── lint.yml           # cppcheck
├── src/                   # Все исходники в одной папке
│   ├── huffman_tree.c/.h
│   ├── priority_queue.c/.h
│   ├── bit_io.c/.h
│   └── compressor.c/.h
├── src_main/
│   └── main.c
├── tests/
│   ├── test_tree.c
│   ├── test_queue.c
│   ├── test_bits.c
│   ├── test_codes.c
│   ├── test_archive.c
│   └── run_all_tests.c
├── experiments/
│   ├── experiment.c/.h
│   ├── analyze_results.py
│   └── run_experiments.sh
├── CMakeLists.txt
└── README.md
```

## Требования

- **CMake** 3.14+
- **C-компилятор** с поддержкой C11 (gcc, clang, MSVC)
- Для тестов: CMocka (скачивается автоматически через FetchContent)

## Сборка

```bash
git clone https://github.com/altrum06/huffman-arhive.git
cd huffman-arhive
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target huffman_app
```

## Использование

```bash
# Сжатие
./build/huffman_app -c <входной_файл> <выходной_архив>

# Распаковка
./build/huffman_app -d <входной_архив> <выходной_файл>

# Справка
./build/huffman_app -h
```

## Тесты

```bash
cmake --build build --target run_tests
cd build && ctest --output-on-failure
# или напрямую:
./build/run_tests
```



Тесты используют библиотеку **CMocka** (автоматически подтягивается через FetchContent).

## Эксперименты

```bash
cd experiments
./run_experiments.sh
```

## Результаты

### Зависимость от размера (текстовый файл, латиница)

| Размер | Исходный | Сжатый | Степень |
|--------|----------|--------|---------|
| 1 KB | 1024 | 744 | 27.3% |
| 10 KB | 10240 | 6239 | 39.1% |
| 50 KB | 51200 | 30657 | 40.1% |
| 100 KB | 102400 | 61180 | 40.3% |
| 500 KB | 512000 | 305365 | 40.4% |

### Медиафайлы

| Тип | Исходный | Сжатый | Степень |
|-----|----------|--------|---------|
| JPEG | 2 MB | ~2 MB | **-0.06%** |
| MP3 | 8.9 MB | 8.9 MB | **0.12%** |
| ZIP | 10.9 MB | 10.9 MB | **-0.01%** |

### Скорость (100 KB, 10 замеров)

| Операция | Среднее | СКО |
|----------|---------|-----|
| Сжатие | ~0.004 сек | ~0.0003 сек |
| Распаковка | ~0.005 сек | ~0.0004 сек |

### Общие выводы

1. Алгоритм эффективен на файлах > 10 КБ (степень сжатия до 40%)
2. Медиафайлы (JPEG, MP3, ZIP) практически не сжимаются (< 1%)
3. Распаковка быстрее сжатия
4. Результаты стабильны (отклонение ~0.01 сек)
