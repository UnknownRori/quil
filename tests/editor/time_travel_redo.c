#include <stddef.h>
#include <assert.h>
#include "editor/time_travel.h"

int main()
{
    UndoStack stack = {0};
    UndoStackPush(&stack, (EditorCmd) {
        .type = EDITOR_CMD_INSERT_CHAR,
        .col = 1,
        .line = 2,
        .character = 'n',
    });
    UndoStackPush(&stack, (EditorCmd) {
        .type = EDITOR_CMD_INSERT_CHAR,
        .col = 1,
        .line = 2,
        .character = 'n',
    });
    UndoStackPrev(&stack);
    UndoStackNext(&stack);
    assert(stack.count == 2 && "Count must be 1");
    assert(stack.top   == 2 && "Top must be 1");
    UndoStackFree(&stack);
    return 0;
}
