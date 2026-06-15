#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdio.h>

/// Поток для побитового чтения из файла
typedef struct {
    FILE *file;           ///< Файловый дескриптор
    unsigned char buffer; ///< Буфер для незавершённого байта
    int bit_count;        ///< Сколько бит осталось в буфере
} BitReader;

/// Поток для побитовой записи в файл
typedef struct {
    FILE *file;           ///< Файловый дескриптор
    unsigned char buffer; ///< Буфер для накопления битов
    int bit_count;        ///< Сколько бит накоплено (0-7)
} BitWriter;

/// Создать читатель битов
BitReader* bit_reader_create(FILE *file);

/// Прочитать один бит (возвращает 0, 1 или -1 при ошибке)
int bit_reader_read_bit(BitReader *reader);

/// Прочитать 8 бит как один байт (MSB first)
int bit_reader_read_byte(BitReader *reader);

/// Прочитать 32 бита как целое число (MSB first)
int bit_reader_read_int(BitReader *reader);

/// Освободить читатель (файл не закрывает)
void bit_reader_free(BitReader *reader);

/// Создать писатель битов
BitWriter* bit_writer_create(FILE *file);

/// Записать один бит
void bit_writer_write_bit(BitWriter *writer, int bit);

/// Записать байт как 8 бит (MSB first)
void bit_writer_write_byte(BitWriter *writer, unsigned char byte);

/// Записать целое число как 32 бита (MSB first)
void bit_writer_write_int(BitWriter *writer, int value);

/// Освободить писатель (файл не закрывает)
void bit_writer_free(BitWriter *writer);

/// Вытолкнуть оставшиеся биты в файл (вызвать после последней записи)
void bit_writer_flush(BitWriter *writer);

#endif
