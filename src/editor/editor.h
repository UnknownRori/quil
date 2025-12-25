#pragma once

#include <rstb_arena.h>
#include "./node.h"

typedef struct Editor {
    rstb_arena arena;

    const char* name;
    int      line_pos, column_pos;
    LineChunk   chunk;
} Editor;

int  EditorInit                 (Editor* e);
int  EditorLoadBuffer           (Editor* e, const char* buffer, size_t n);
void EditorReset                (Editor* e);
void EditorUnload               (Editor* e);

Line* EditorGetLine             (Editor* e, size_t line);
size_t EditorGetTotalLine       (Editor* e);

void EditorIncSelectedLine                  (Editor* e, int n);
void EditorIncSelectedColumn                (Editor* e, int n);
void EditorSetSelectedColumnBeginning       (Editor* e);
void EditorSetSelectedColumnEnd             (Editor* e);

void EditorRemoveCharOnCurrentCursor      (Editor* e);
void EditorAddNewLineOnCurrentCursor      (Editor* e);
void EditorAppendCharOnCurrentCursor      (Editor* e, char n);
