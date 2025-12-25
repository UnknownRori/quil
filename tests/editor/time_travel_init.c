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
    assert(stack.count == 1 && "Count must be 1");
    assert(stack.top   == 1 && "Top must be 1");
    EditorCmd cmd = UndoStackCurrent(&stack);
    assert(cmd.type == EDITOR_CMD_INSERT_CHAR);
    assert(cmd.col  == 1);
    assert(cmd.line == 2);
    assert(cmd.character == 'n');

    UndoStackFree(&stack);
    return 0;
}
