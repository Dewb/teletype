#include "teletype.h"

#include <ctype.h>
#include <stdint.h>

// copied from globals.h -- todo: reunify somehow
#ifndef SCENE_TEXT_LINES
#define SCENE_TEXT_LINES 32
#endif
#ifndef SCENE_TEXT_CHARS
#define SCENE_TEXT_CHARS 32
#endif

typedef struct {
    void (*write_buffer)(void* user_data, uint8_t* buffer, uint16_t size);
    void (*write_char)(void* user_data, uint8_t c);
    void (*print_dbg)(const char* str);
    void* data;
} tt_serializer_t;

typedef struct {
    uint16_t (*read_char)(void* user_data);
    bool (*eof)(void* user_data);
    void (*print_dbg)(const char* str);
    void* data;
} tt_deserializer_t;

void serialize_scene(tt_serializer_t* stream, uint8_t scene_num, scene_state_t* scene, char (*text)[32][32]);
void deserialize_scene(tt_deserializer_t* stream, uint8_t scene_num, scene_state_t* scene, char (*text)[32][32]);

void serialize_grid(tt_serializer_t* stream, scene_state_t* scene);
void deserialize_grid(tt_deserializer_t* stream, scene_state_t* scene, char c);
