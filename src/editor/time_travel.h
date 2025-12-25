#pragma once

typedef enum EditorCmdType {
    EDITOR_CMD_INSERT_CHAR,
    EDITOR_CMD_DELETE_CHAR,
    EDITOR_CMD_INSERT_LINE,
} EditorCmdType;

typedef struct EditorCmd {
    EditorCmdType type;
    int  line, col;
    char character;
} EditorCmd;

typedef struct UndoStack {
    EditorCmd* items;
    size_t     count;
    size_t     capacity;
    size_t     top;
} UndoStack;

void        UndoStackReset      (UndoStack*);
void        UndoStackFree       (UndoStack*);
void        UndoStackPush       (UndoStack*, EditorCmd);
void        UndoStackNext       (UndoStack*);
void        UndoStackPrev       (UndoStack*);
EditorCmd   UndoStackCurrent    (UndoStack*);
