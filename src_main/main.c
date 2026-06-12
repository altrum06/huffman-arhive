#include "../src/archive/compressor.h"
#include <stdio.h>
#include <string.h>

void print_usage(const char* program_name) {
    printf("Usage:\n");
    printf("  %s -c <input> <output>   Compress file\n", program_name);
    printf("  %s -d <input> <output>   Decompress file\n", program_name);
    printf("  %s -h                    Show help\n", program_name);
}

int main(int argc, char* argv[]) {
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

        printf("Compressing %s -> %s\n", argv[2], argv[3]);
        int result = compress_file(argv[2], argv[3]);

        if (result == 0) {
            printf("Success!\n");
        } else {
            printf("Failed!\n");
            return 1;
        }
    }
    else if (strcmp(argv[1], "-d") == 0) {
        if (argc < 4) {
            printf("Error: Missing input or output file\n");
            return 1;
        }

        printf("Decompressing %s -> %s\n", argv[2], argv[3]);
        int result = decompress_file(argv[2], argv[3]);

        if (result == 0) {
            printf("Success!\n");
        } else {
            printf("Failed!\n");
            return 1;
        }
    }
    else {
        printf("Unknown option: %s\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}