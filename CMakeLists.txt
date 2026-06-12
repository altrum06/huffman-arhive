cmake_minimum_required(VERSION 3.10)
project(huffman_archive)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Основная программа
add_executable(huffman_app
    src_main/main.c
    src/queue/priority_queue.c
    src/tree/huffman_tree.c
    src/bits/bit_io.c
    src/archive/compressor.c
)

target_include_directories(huffman_app PRIVATE
    src
    src/queue
    src/tree
    src/bits
    src/archive
)

target_compile_options(huffman_app PRIVATE -Wall -Wextra)

# Тесты
add_executable(run_tests
    tests/test_tree.c
    tests/test_queue.c
    tests/test_bits.c
    tests/test_codes.c
    tests/test_archive.c
    src/queue/priority_queue.c
    src/tree/huffman_tree.c
    src/bits/bit_io.c
    src/archive/compressor.c
)

target_include_directories(run_tests PRIVATE
    src
    src/queue
    src/tree
    src/bits
    src/archive
)

target_compile_options(run_tests PRIVATE -Wall -Wextra)

# Включить тестирование
enable_testing()
add_test(NAME huffman_test COMMAND run_tests)
