#include "serialize_scene_tests.h"
#include <stdlib.h>
#include <string.h>

#include "greatest/greatest.h"

#include "log.h"
#include "teletype.h"
#include "state.h"
#include "serializer.h"
#include "serialize.h"

void test_file_write_buffer(void* user_data, uint8_t* buffer, uint16_t size) {
    fwrite(buffer, 1, size, (FILE*)user_data);
}
void test_file_write_char(void* user_data, uint8_t c) {
    fputc(c, (FILE*)user_data);
}
void test_print_dbg(const char* c) {
    printf("%s\n", c);
}

uint16_t test_file_read_char(void* user_data) {
    return (uint16_t)fgetc((FILE*)user_data);
}
bool test_file_eof(void* user_data) {
    return feof((FILE*)user_data) != 0;
}

tt_serializer_t test_writer;
tt_deserializer_t test_reader;

void init_streams()
{
    test_writer.write_buffer = &test_file_write_buffer;
    test_writer.write_char = &test_file_write_char;
    test_writer.print_dbg = &test_print_dbg;

    test_reader.read_char = &test_file_read_char;
    test_reader.eof = &test_file_eof;
    test_reader.print_dbg = &test_print_dbg;
}

int compare_files(char* filename, FILE* a, FILE* b) {
    fseek(a, 0, 0);
    fseek(b, 0, 0);

    int line = 1;

    while (!feof(a) && !feof(b)) {
        char ca = fgetc(a);
        char cb = fgetc(b);
        if (ca != cb) {
            lprintf("At %s line %d, expected '%c', got '%c'", filename, line, ca, cb);
            return -1;
        }
        if (ca == '\n')
        {
            line++;
        }
    }

    if (feof(a) != feof(b)) {
        return -1;
    }

    return 0;
}

TEST test_round_trip_preset(char* filename, char* tempfile) 
{
    scene_state_t scene;
    ss_init(&scene);

    char text[SCENE_TEXT_LINES][SCENE_TEXT_CHARS];
    memset(text, 0, SCENE_TEXT_LINES * SCENE_TEXT_CHARS);

    for (int i = 0; i < 9; i++)
    {
        FILE* infile = fopen(filename, "rb");
        ASSERT(infile != 0);
        test_reader.data = (void*)infile;

        deserialize_scene(&test_reader, &scene, &text);

        FILE* outfile = fopen(tempfile, "w+b");
        ASSERT(outfile != 0);
        test_writer.data = (void*)outfile;

        serialize_scene(&test_writer, &scene, &text);

        CHECK_CALL(compare_files(filename, infile, outfile));
    }

    PASS();
}

SUITE(serialize_scene_suite) {
    log_init();
    init_streams();
    RUN_TESTp(test_round_trip_preset, "../presets/tt00.txt", "./results/tt00.txt");
    RUN_TESTp(test_round_trip_preset, "../presets/tt01.txt", "./results/tt01.txt");
    RUN_TESTp(test_round_trip_preset, "../presets/tt02.txt", "./results/tt02.txt");
    RUN_TESTp(test_round_trip_preset, "../presets/tt03.txt", "./results/tt03.txt");
    RUN_TESTp(test_round_trip_preset, "../presets/tt04.txt", "./results/tt04.txt");
    // no ii ops loaded in this binary
    // RUN_TESTp(test_round_trip_preset, "../presets/tt05.txt", "./results/tt05.txt");
    // RUN_TESTp(test_round_trip_preset, "../presets/tt06.txt", "./results/tt06.txt");
    // RUN_TESTp(test_round_trip_preset, "../presets/tt07.txt", "./results/tt07.txt");
    RUN_TESTp(test_round_trip_preset, "../presets/tt08.txt", "./results/tt08.txt");
    log_print();
}
