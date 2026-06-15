#include "../src/compressor.h"
#include <stdio.h>
#include <string.h>

// Показать справку по использованию программы
static void print_usage(const char *program_name) {
    printf("Usage:\n");
    printf("  %s -c <input> <output>   Compress file\n", program_name);
    printf("  %s -d <input> <output>   Decompress file\n", program_name);
    printf("  %s -h                    Show help\n", program_name);
}

// Вернуть строку с описанием кода ошибки
static const char* error_message(int code) {
    switch (code) {
        case COMPRESS_ERR_OPEN:  return "Cannot open file";
        case COMPRESS_ERR_MEM:   return "Memory allocation failed";
        case COMPRESS_ERR_READ:  return "File read error";
        case COMPRESS_ERR_WRITE: return "File write error";
        case COMPRESS_ERR_DATA:  return "Corrupt or invalid data";
        default:                 return "Unknown error";
    }
}

// Точка входа: парсинг аргументов и вызов compress_file / decompress_file
int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0) {
        if (argc < 4) {
            printf("Error: Missing input or output file\n");
            return 1;
        }

        int result = compress_file(argv[2], argv[3]);
        if (result == COMPRESS_SUCCESS) {
            printf("Success: %s -> %s\n", argv[2], argv[3]);
        } else {
            printf("Error: %s\n", error_message(result));
            return 1;
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        if (argc < 4) {
            printf("Error: Missing input or output file\n");
            return 1;
        }

        int result = decompress_file(argv[2], argv[3]);
        if (result == COMPRESS_SUCCESS) {
            printf("Success: %s -> %s\n", argv[2], argv[3]);
        } else {
            printf("Error: %s\n", error_message(result));
            return 1;
        }
    } else {
        printf("Unknown option: %s\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
