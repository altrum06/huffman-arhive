#include "bit_io.h"
#include <stdlib.h>

BitWriter* bit_writer_create(FILE *file) {
    BitWriter* bit_writer = (BitWriter*)malloc(sizeof(BitWriter));

    if (bit_writer == NULL) {
        return NULL;
    }

    // Сохраняем файл и подготавливаем пустой битовый буфер
    bit_writer->file = file;
    bit_writer->buffer = 0;
    bit_writer->bit_count = 0;

    return bit_writer;
}

void bit_writer_write_bit(BitWriter* bit_writer, int bit) {
    if (bit_writer == NULL || bit_writer->file == NULL) {
        return;
    }

    // Если записываем 1, ставим нужный бит в буфере
    if (bit) {
        bit_writer->buffer |= (1 << (7 - bit_writer->bit_count));
    }

    bit_writer->bit_count++;

    // Когда набралось 8 бит, записываем целый байт в файл
    if (bit_writer->bit_count == 8) {
        fputc(bit_writer->buffer, bit_writer->file);
        bit_writer->bit_count = 0;
        bit_writer->buffer = 0;
    }
}

void bit_writer_write_byte(BitWriter* bit_writer, unsigned char byte) {
    if (bit_writer == NULL) {
        return;
    }

    // Записываем байт побитово, начиная со старшего бита
    for (int i = 7; i >= 0; i--) {
        bit_writer_write_bit(bit_writer, (byte >> i) & 1);
    }
}

void bit_writer_write_int(BitWriter* bit_writer, int value) {
    if (bit_writer == NULL) {
        return;
    }

    // Записываем int как 32 бита, начиная со старшего
    for (int i = 31; i >= 0; i--) {
        bit_writer_write_bit(bit_writer, (value >> i) & 1);
    }
}

void bit_writer_flush(BitWriter* bit_writer) {
    if (bit_writer == NULL || bit_writer->file == NULL) {
        return;
    }

    // Если в буфере остались незаписанные биты, дописываем их в файл
    if (bit_writer->bit_count > 0) {
        fputc(bit_writer->buffer, bit_writer->file);
        bit_writer->bit_count = 0;
        bit_writer->buffer = 0;
    }
}

void bit_writer_free(BitWriter* bit_writer) {
    free(bit_writer);
}

BitReader* bit_reader_create(FILE *file) {
    BitReader* bit_reader = (BitReader*)malloc(sizeof(BitReader));

    if (bit_reader == NULL) {
        return NULL;
    }

    // Подготавливаем структуру для чтения битов из файла
    bit_reader->file = file;
    bit_reader->buffer = 0;
    bit_reader->bit_count = 0;

    return bit_reader;
}

int bit_reader_read_bit(BitReader* bit_reader) {
    if (bit_reader == NULL || bit_reader->file == NULL) {
        return -1;
    }

    // Если все биты из буфера уже прочитаны, читаем новый байт из файла
    if (bit_reader->bit_count == 0) {
        int byte = fgetc(bit_reader->file);

        if (byte == EOF) {
            return -1;
        }

        bit_reader->buffer = (unsigned char)byte;
        bit_reader->bit_count = 8;
    }

    bit_reader->bit_count--;

    // Возвращаем очередной бит из буфера
    return (bit_reader->buffer >> bit_reader->bit_count) & 1;
}

int bit_reader_read_byte(BitReader* bit_reader) {
    unsigned char result = 0;

    // Собираем байт из 8 прочитанных битов
    for (int i = 7; i >= 0; i--) {
        int bit = bit_reader_read_bit(bit_reader);

        if (bit == -1) {
            return -1;
        }

        if (bit) {
            result |= (1 << i);
        }
    }

    return result;
}

int bit_reader_read_int(BitReader* bit_reader) {
    int result = 0;

    // Собираем int из 32 прочитанных битов
    for (int i = 31; i >= 0; i--) {
        int bit = bit_reader_read_bit(bit_reader);

        if (bit == -1) {
            return -1;
        }

        if (bit) {
            result |= (1 << i);
        }
    }

    return result;
}

void bit_reader_free(BitReader* bit_reader) {
    free(bit_reader);
}

