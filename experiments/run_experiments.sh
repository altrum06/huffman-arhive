#!/bin/bash

echo "Запуск экспериментов"

# Переход в нужную папку
cd /mnt/c/Users/Adam/CLionProjects/huffman-arhive/experiments

# Компиляция
gcc -o experiment experiment.c ../src/compressor.c ../src/huffman_tree.c ../src/priority_queue.c ../src/bit_io.c -I.. -lm

# Запуск
./experiment

echo "Готово!"
