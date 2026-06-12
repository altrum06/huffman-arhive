#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdio.h>

typedef struct {
    FILE* file;
    unsigned char buffer;
    int bit_count;
}BitReader;

typedef struct {
    FILE* file;
    unsigned char buffer;
    int bit_count;
}BitWriter;


BitReader* bit_reader_create(FILE *file);
int bit_reader_read_bit(BitReader* bit_reader);
int bit_reader_read_byte(BitReader* bit_reader);
int  bit_reader_read_int(BitReader* bit_reader);
void bit_reader_free(BitReader* bit_reader);


BitWriter* bit_writer_create(FILE *file);
void bit_writer_write_bit(BitWriter* bit_writer, int bit);
void bit_writer_write_byte(BitWriter* bit_writer, unsigned char byte);
void bit_writer_write_int(BitWriter* bit_writer, int value);
void bit_writer_free(BitWriter* bit_writer);
void bit_writer_flush(BitWriter* bit_writer);

#endif




