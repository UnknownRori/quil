#include <rstb_arena.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "editor.h"
#include "editor/node.h"
#include "rstb_da.h"

int  EditorInit  (Editor* e)
{
    assert(e != NULL);
    memset(e, 0, sizeof(Editor));
    rstb_arena_init(&e->arena, RSTB_ARENA_RECOMMENDED * 2);
    rstb_da_reserve(&e->chunk, 10);
    return 0;
}

int  EditorLoadBuffer   (Editor* e, const char* buffer, size_t n)
{
    assert(e != NULL || buffer != NULL);

    size_t copy_count = 0;
    size_t i;
    for (i = 0; i < n; i++) {
        if (buffer[i] == '\n') {
            Line l;
            const char* start = buffer + i - copy_count;
            l.buffer = rstb_arena_alloc(&e->arena, copy_count + 1);
            memcpy(l.buffer, start, copy_count);
            l.buffer[copy_count + 1] = 0;
            l.capacity = copy_count;
            l.count = copy_count;
            rstb_da_append(&e->chunk, l);
        }
        copy_count++;
    }

    if (copy_count > 0) {
        Line l;
        const char* start = buffer + i - copy_count;
        l.buffer = rstb_arena_alloc(&e->arena, copy_count + 1);
        memcpy(l.buffer, start, copy_count);
        l.buffer[copy_count + 1] = 0;
        l.capacity = copy_count;
        l.count = copy_count;
        rstb_da_append(&e->chunk, l);
    }

    return 0;
}

void EditorReset (Editor* e)
{
    assert(e != NULL);
    rstb_arena_reset(&e->arena);
    rstb_da_reset(&e->chunk);
    e->line_pos = 0;
    e->column_pos = 0;
    e->name = NULL;
}

void EditorUnload(Editor* e)
{
    assert(e != NULL);
    rstb_arena_free(&e->arena);
    rstb_da_free(&e->chunk);
    memset(e, 0, sizeof(Editor));
}

Line* EditorGetLine             (Editor* e, size_t line)
{
    assert(e != NULL);
    assert(e->chunk.count > line);
    return &e->chunk.items[line];
}

size_t EditorGetTotalLine      (Editor* e)
{
    assert(e != NULL);
    return e->chunk.count;
}
