#include <rstb_arena.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "editor.h"
#include "editor/node.h"
#include "rstb_da.h"
#include "time_travel.h"

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

void EditorSetSelectedLine                  (Editor* e, int n)
{
    assert(e != NULL);
    assert(e->chunk.count > n);
    e->line_pos = n;
}
void EditorSetSelectedColumn                (Editor* e, int n)
{
    assert(e != NULL);
    Line* l = EditorGetLine(e, e->line_pos);
    assert(l->count + 1 > n);
    e->column_pos = n;
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

static void _EditorRemoveCharOnCursor(Editor* e, bool record)
{
    assert(e != NULL);
    if (e->column_pos == 0) {
        assert(0 && "Not Implemented");
        return ;
    }
    Line* l = EditorGetLine(e, e->line_pos);
    char n = l->items[e->column_pos-1];
    memmove(
        l->items + e->column_pos - 1, 
        l->items + e->column_pos, 
        l->count - e->column_pos
    );

    if (record) {
        UndoStackPush(&e->time_travel, (EditorCmd) {
            .type = EDITOR_CMD_INSERT_CHAR,
            .line = e->line_pos,
            .col  = e->column_pos,
            .character = n,
        });
    }

    l->count -= 1;
    l->items[l->count] = '\0';
    EditorIncSelectedColumn(e, -1);
}

void EditorRemoveCharOnCurrentCursor      (Editor* e)
{
    _EditorRemoveCharOnCursor(e, true);
}

static void _EditorAppendCharOnCurrentCursor(Editor* e, char n, bool record)
{
    assert(e != NULL);
    Line* l = EditorGetLine(e, e->line_pos);
    rstb_da_reserve(l, l->count + 2);
    memmove(l->items + e->column_pos + 1, l->items + e->column_pos, l->count - e->column_pos);

    if (record) {
        printf("push:%c\n", n);
        UndoStackPush(&e->time_travel, (EditorCmd) {
            .type = EDITOR_CMD_INSERT_CHAR,
            .line = e->line_pos,
            .col  = e->column_pos,
            .character = n,
        });
    }

    l->items[e->column_pos] = n;
    l->count += 1;
    l->items[l->count + 1] = '\0';
    EditorIncSelectedColumn(e, 1);
}

void EditorAppendCharOnCurrentCursor      (Editor* e, char n)
{
    _EditorAppendCharOnCurrentCursor(e, n, true);
}

static void _EditorAddNewLineOnCurrentCursor(Editor* e, bool record)
{
    assert(e != NULL);
    if ((e->line_pos + 1) > e->chunk.count) {
        return;
    }
    rstb_da_reserve(&e->chunk, e->chunk.count + 1);
    memmove(e->chunk.items + e->line_pos + 1, e->chunk.items + e->line_pos, sizeof(Line) * e->chunk.count - sizeof(Line) * e->line_pos);

    Line* l = EditorGetLine(e, e->line_pos);
    LineReset(l);

    UndoStackPush(&e->time_travel, (EditorCmd) {
        .type = EDITOR_CMD_INSERT_LINE,
        .line = e->line_pos,
        .col  = e->column_pos,
    });

    e->chunk.count += 1;
    EditorIncSelectedLine(e, 1);
}


void EditorAddNewLineOnCurrentCursor      (Editor* e)
{
    _EditorAddNewLineOnCurrentCursor(e, true);
}

void EditorUndo                             (Editor* e)
{
    assert(e != NULL);
    if (e->time_travel.top <= 0) {
        return;
    }
    UndoStackPrev(&e->time_travel);
    EditorCmd cmd = UndoStackCurrent(&e->time_travel);
    switch (cmd.type) {
        case EDITOR_CMD_INSERT_CHAR:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col + 1);
            _EditorRemoveCharOnCursor(e, false);
            break;
        case EDITOR_CMD_DELETE_CHAR:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col);
            _EditorAppendCharOnCurrentCursor(e, cmd.character, false);
            break;
        case EDITOR_CMD_INSERT_LINE:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col);
            _EditorAddNewLineOnCurrentCursor(e, false);
            break;
    }
}

void EditorRedo                             (Editor* e)
{
    assert(e != NULL);
    if (e->time_travel.top >= e->time_travel.count) {
        return;
    }
    EditorCmd cmd = UndoStackCurrent(&e->time_travel);
    UndoStackNext(&e->time_travel);
    switch (cmd.type) {
        case EDITOR_CMD_INSERT_CHAR:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col);
            _EditorAppendCharOnCurrentCursor(e, cmd.character, false);
            break;
        case EDITOR_CMD_DELETE_CHAR:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col);
            _EditorRemoveCharOnCursor(e, false);
            break;
        case EDITOR_CMD_INSERT_LINE:
            EditorSetSelectedLine(e, cmd.line);
            EditorSetSelectedColumn(e, cmd.col);
            _EditorAddNewLineOnCurrentCursor(e, false);
            break;
    }
}
