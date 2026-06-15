#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#define COMPRESS_SUCCESS    0   ///< Успешное завершение операции
#define COMPRESS_ERR_OPEN  -1   ///< Не удалось открыть файл
#define COMPRESS_ERR_MEM   -2   ///< Ошибка выделения памяти
#define COMPRESS_ERR_READ  -3   ///< Ошибка чтения данных
#define COMPRESS_ERR_WRITE -4   ///< Ошибка записи данных
#define COMPRESS_ERR_DATA  -5   ///< Испорченный или неверный формат данных

/// Сжать файл
int compress_file(const char *input_file, const char *output_file);

/// Распаковать файл
int decompress_file(const char *input_file, const char *output_file);

#endif
