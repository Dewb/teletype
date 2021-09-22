#include <stdint.h>
#include <stdbool.h>

#ifndef _TT_SERIALIZER_H
#define _TT_SERIALIZER_H

typedef struct
{
    void (*write_buffer)(void* user_data, uint8_t* buffer, uint16_t size);
    void (*write_char)(void* user_data, uint8_t c);
    void (*print_dbg)(const char* str);
    void* data;
} tt_serializer_t;

typedef struct
{
    uint16_t (*read_char)(void* user_data);
    bool (*eof)(void* user_data);
    void (*print_dbg)(const char* str);
    void* data;
} tt_deserializer_t;

#endif