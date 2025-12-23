#pragma once

#include <rstb_arena.h>
#include "./node.h"

typedef struct Editor {
    rstb_arena arena;

    const char* name;
    size_t      line_pos, column_pos;
    Line*       line;
} Editor;

int  EditorInit         (Editor* e);
int  EditorLoadBuffer   (Editor* e, const char* buffer, size_t n);
void EditorReset        (Editor* e);
void EditorUnload       (Editor* e);
