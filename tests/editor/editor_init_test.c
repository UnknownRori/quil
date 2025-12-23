#include <stddef.h>
#include <assert.h>
#include "editor/editor.h"

int main()
{
    Editor e = {0};
    EditorInit(&e);

    assert(e.arena.region_size != 0 && "Arena not initialized");
    assert(e.column_pos == 0 && "Column position must be at 0");
    assert(e.line_pos == 0 && "Line position must be at 0");
    assert(e.line == NULL && "Line must be not initialized");
    assert(e.name == NULL && "Name must be not initialized");

    EditorUnload(&e);
    return 0;
}
