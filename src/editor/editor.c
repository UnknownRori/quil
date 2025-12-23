#include <rstb_arena.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "editor.h"
#include "editor/node.h"

int  EditorInit  (Editor* e)
{
    assert(e != NULL);
    memset(e, 0, sizeof(Editor));
    rstb_arena_init(&e->arena, RSTB_ARENA_RECOMMENDED * 2);
    return 0;
}

int  EditorLoadBuffer   (Editor* e, const char* buffer, size_t n)
{
    assert(e != NULL || buffer != NULL);
    if (e->line == NULL) {
        e->line = LineInit(&e->arena);
    }
    Line* l = e->line;
    size_t copy_count = 0;
    for (size_t i = 0; i < n; i++) {
        if (buffer[i] == '\n') {
            const char* start = buffer + i - copy_count;
            l->buffer = rstb_arena_alloc(&e->arena, copy_count + 1);
            memcpy(l->buffer, start, copy_count);
            l->buffer[copy_count + 1] = 0;
            l->capacity = copy_count;
            l->end = copy_count;


            l->next = LineInit(&e->arena);
            l->next->prev = l;
            l = l->next;
        }
        copy_count++;
    }

    return 0;
}

void EditorReset (Editor* e)
{
    assert(e != NULL);
    rstb_arena_reset(&e->arena);
    e->line_pos = 0;
    e->column_pos = 0;
    e->name = NULL;
}

void EditorUnload(Editor* e)
{
    assert(e != NULL);
    rstb_arena_free(&e->arena);
    memset(e, 0, sizeof(Editor));
}
