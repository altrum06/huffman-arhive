#include "bit_io.h"
#include <stdlib.h>

// Создать писатель битов
BitWriter* bit_writer_create(FILE *file) {
    BitWriter *writer = malloc(sizeof(BitWriter));
    if (writer == NULL) return NULL;
    writer->file = file;
    writer->buffer = 0;
    writer->bit_count = 0;
    return writer;
}

// Записать один бит (накапливает в буфере, сбрасывает в файл по накоплении 8 бит)
void bit_writer_write_bit(BitWriter *writer, int bit) {
    if (writer == NULL || writer->file == NULL) return;
    if (bit) {
        writer->buffer |= (1 << (7 - writer->bit_count));
    }
    writer->bit_count++;
    if (writer->bit_count == 8) {
        fputc(writer->buffer, writer->file);
        writer->bit_count = 0;
        writer->buffer = 0;
    }
}

// Записать байт как 8 бит (старший бит первым)
void bit_writer_write_byte(BitWriter *writer, unsigned char byte) {
    if (writer == NULL) return;
    for (int i = 7; i >= 0; i--) {
        bit_writer_write_bit(writer, (byte >> i) & 1);
    }
}

// Записать целое число как 32 бита (старший бит первым)
void bit_writer_write_int(BitWriter *writer, int value) {
    if (writer == NULL) return;
    for (int i = 31; i >= 0; i--) {
        bit_writer_write_bit(writer, (value >> i) & 1);
    }
}

// Вытолкнуть оставшиеся биты в файл
void bit_writer_flush(BitWriter *writer) {
    if (writer == NULL || writer->file == NULL) return;
    if (writer->bit_count > 0) {
        fputc(writer->buffer, writer->file);
        writer->bit_count = 0;
        writer->buffer = 0;
    }
}

// Освободить писатель
void bit_writer_free(BitWriter *writer) {
    free(writer);
}

// Создать читатель битов
BitReader* bit_reader_create(FILE *file) {
    BitReader *reader = malloc(sizeof(BitReader));
    if (reader == NULL) return NULL;
    reader->file = file;
    reader->buffer = 0;
    reader->bit_count = 0;
    return reader;
}

// Прочитать один бит (читает байт из файла, когда буфер пуст)
int bit_reader_read_bit(BitReader *reader) {
    if (reader == NULL || reader->file == NULL) return -1;
    if (reader->bit_count == 0) {
        int byte = fgetc(reader->file);
        if (byte == EOF) return -1;
        reader->buffer = (unsigned char)byte;
        reader->bit_count = 8;
    }
    reader->bit_count--;
    return (reader->buffer >> reader->bit_count) & 1;
}

// Прочитать 8 бит и собрать в байт
int bit_reader_read_byte(BitReader *reader) {
    unsigned char result = 0;
    for (int i = 7; i >= 0; i--) {
        int bit = bit_reader_read_bit(reader);
        if (bit == -1) return -1;
        if (bit) result |= (1 << i);
    }
    return result;
}

// Прочитать 32 бита и собрать в целое число
int bit_reader_read_int(BitReader *reader) {
    int result = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = bit_reader_read_bit(reader);
        if (bit == -1) return -1;
        if (bit) result |= (1 << i);
    }
    return result;
}

// Освободить читатель
void bit_reader_free(BitReader *reader) {
    free(reader);
}
