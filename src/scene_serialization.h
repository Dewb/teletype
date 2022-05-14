#include "state.h"
#include "serializer.h"
#include "scene_serialization_constants.h"
#include <ctype.h>
#include <stdint.h>

void serialize_scene(tt_serializer_t* stream, scene_state_t* scene, char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]);
void deserialize_scene(tt_deserializer_t* stream, scene_state_t* scene, char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]);
