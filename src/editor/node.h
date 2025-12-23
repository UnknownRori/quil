#pragma once

#include <rstb_arena.h>

typedef struct Line {
    char*  buffer;
    size_t end;
    size_t capacity;

    struct Line* prev;
    struct Line* next;
} Line;

Line* LineInit(rstb_arena*);
