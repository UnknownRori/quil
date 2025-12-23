#pragma once

#include <rstb_arena.h>
#include <rstb_da.h>

typedef struct Line {
    char*  buffer;
    size_t count;
    size_t capacity;
} Line;

rstb_da_decl(Line, LineChunk);

Line* LineInit(rstb_arena*);
