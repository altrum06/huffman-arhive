cmake_minimum_required(VERSION 3.14)
project(huffman_archive)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cmocka
    GIT_REPOSITORY https://gitlab.com/cmocka/cmocka.git
    GIT_TAG cmocka-1.1.7
)
set(CMOCKA_INSTALL OFF)
set(CMOCKA_BUILD_TESTS OFF)
set(CMOCKA_BUILD_EXAMPLES OFF)
FetchContent_MakeAvailable(cmocka)

add_executable(huffman_app
    src_main/main.c
    src/priority_queue.c
    src/huffman_tree.c
    src/bit_io.c
    src/compressor.c
)

target_include_directories(huffman_app PRIVATE
    src
)

target_compile_options(huffman_app PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<C_COMPILER_ID:Clang>:-Wall -Wextra>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

add_executable(run_tests
    tests/test_tree.c
    tests/test_queue.c
    tests/test_bits.c
    tests/test_codes.c
    tests/test_archive.c
    tests/run_all_tests.c
    src/priority_queue.c
    src/huffman_tree.c
    src/bit_io.c
    src/compressor.c
)

target_include_directories(run_tests PRIVATE
    src
)

target_compile_options(run_tests PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<C_COMPILER_ID:Clang>:-Wall -Wextra>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

target_link_libraries(run_tests PRIVATE cmocka::cmocka)

# Включаем тестирование только для нашей цели (не для CMocka)
enable_testing()
add_test(NAME huffman_test COMMAND run_tests)
