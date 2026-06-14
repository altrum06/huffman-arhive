#!/bin/bash

echo "Запуск экспериментов"

# Переход в нужную папку
cd /mnt/c/Users/Adam/CLionProjects/huffman-arhive/experiments

# Компиляция
gcc -o experiment experiment.c ../src/archive/compressor.c ../src/tree/huffman_tree.c ../src/queue/priority_queue.c ../src/bits/bit_io.c -I.. -lm

# Запуск
./experiment

echo "Готово!"
