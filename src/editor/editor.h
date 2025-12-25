#pragma once

#include <rstb_arena.h>
#include "./node.h"
#include "./time_travel.h"

typedef struct Editor {
    rstb_arena arena;

    const char* name;
    int         line_pos, column_pos;
    LineChunk   chunk;
    UndoStack   time_travel;
} Editor;

int  EditorInit                             (Editor* e);
int  EditorLoadBuffer                       (Editor* e, const char* buffer, size_t n);
void EditorReset                            (Editor* e);
void EditorUnload                           (Editor* e);

Line* EditorGetLine                         (Editor* e, size_t line);
size_t EditorGetTotalLine                   (Editor* e);

void EditorSetSelectedLine                  (Editor* e, int n);
void EditorSetSelectedColumn                (Editor* e, int n);
void EditorIncSelectedLine                  (Editor* e, int n);
void EditorIncSelectedColumn                (Editor* e, int n);
void EditorSetSelectedColumnBeginning       (Editor* e);
void EditorSetSelectedColumnEnd             (Editor* e);

void EditorUndo                             (Editor* e);
void EditorRedo                             (Editor* e);

void EditorRemoveCharOnCurrentCursor        (Editor* e);
void EditorAddNewLineOnCurrentCursor        (Editor* e);
void EditorAppendCharOnCurrentCursor        (Editor* e, char n);
