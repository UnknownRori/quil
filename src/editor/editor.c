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
    Line l = {0};
    for(size_t i = 0; i < n; i++) {
        if (buffer[i] == '\n') {
            rstb_da_append(&e->chunk, l);
            l = (Line){0};
            continue;
        }

        rstb_da_append(&l, buffer[i]);
    }
    rstb_da_append(&e->chunk, l);

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

void EditorIncSelectedLine      (Editor* e, int n)
{
    assert(e != NULL);
    e->line_pos += n;
    if (e->line_pos > (int)e->chunk.count - 1) {
        e->line_pos = e->chunk.count - 1;
    }

    if (e->line_pos < 0) {
        e->line_pos = 0;
    }

    EditorIncSelectedColumn(e, 0);
}
void EditorIncSelectedColumn    (Editor* e, int n)
{
    assert(e != NULL);
    e->column_pos += n;
    Line* l = EditorGetLine(e, e->line_pos);
    if (e->column_pos < 0) {
        e->column_pos = 0;
    } else if (e->column_pos > l->count) {
        e->column_pos = l->count;
    }

}

void EditorSetSelectedColumnBeginning       (Editor* e)
{
    assert(e != NULL);
    e->column_pos = 0;
}

void EditorSetSelectedColumnEnd             (Editor* e)
{
    Line* l = EditorGetLine(e, e->line_pos);
    e->column_pos = l->count;
}

void EditorRemoveCharOnCurrentCursor      (Editor* e)
{
    assert(e != NULL);
    if (e->column_pos == 0) {
        assert(0 && "Not Implemented");
        return ;
    }
    Line* l = EditorGetLine(e, e->line_pos);
    memmove(
        l->items + e->column_pos - 1, 
        l->items + e->column_pos, 
        l->count - e->column_pos
    );
    l->count -= 1;
    l->items[l->count] = '\0';
    EditorIncSelectedColumn(e, -1);
}

void EditorAppendCharOnCurrentCursor      (Editor* e, char n)
{
    assert(e != NULL);
    Line* l = EditorGetLine(e, e->line_pos);
    rstb_da_reserve(l, l->count + 2);
    memmove(l->items + e->column_pos + 1, l->items + e->column_pos, l->count - e->column_pos);
    l->items[e->column_pos] = n;
    l->count += 1;
    l->items[l->count + 1] = '\0';
    EditorIncSelectedColumn(e, 1);
}

void EditorAddNewLineOnCurrentCursor      (Editor* e)
{
    assert(e != NULL);
    if ((e->line_pos + 1) > e->chunk.count) {
        return;
    }
    rstb_da_reserve(&e->chunk, e->chunk.count + 1);
    memmove(e->chunk.items + e->line_pos + 1, e->chunk.items + e->line_pos, sizeof(Line) * e->chunk.count - sizeof(Line) * e->line_pos);

    Line* l = EditorGetLine(e, e->line_pos);
    LineReset(l);


    e->chunk.count += 1;
    EditorIncSelectedLine(e, 1);
}
