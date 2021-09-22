#include "state.h"
#include "serializer.h"
#include <ctype.h>
#include <stdint.h>

#define SCENE_TEXT_LINES 32
#define SCENE_TEXT_CHARS 32

void serialize_scene(tt_serializer_t* stream, scene_state_t* scene, char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]);
void deserialize_scene(tt_deserializer_t* stream, scene_state_t* scene, char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]);

void serialize_grid(tt_serializer_t* stream, scene_state_t* scene);
void deserialize_grid(tt_deserializer_t* stream, scene_state_t* scene, char c);
