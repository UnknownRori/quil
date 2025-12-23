#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "editor/editor.h"

const char* contents = "Agus\nPamungkas\nBambang";

int main()
{
    Editor e = {0};
    EditorInit(&e);

    EditorLoadBuffer(&e, contents, strlen(contents));
    assert(e.name == NULL && "File name must not is not initialized");
    assert(EditorGetTotalLine(&e) == 3 && "Line must be 3");

    Line* l = EditorGetLine(&e, 0);
    assert(strcmp(l->buffer, "Agus\n") && "1st line must be Agus");

    l = EditorGetLine(&e, 1);
    assert(strcmp(l->buffer, "Pamungkas\n") && "2nd line must Pamungkas");

    l = EditorGetLine(&e, 2);
    assert(strcmp(l->buffer, "Bambang") && "3rd line must Bambang");

    EditorUnload(&e);

    return 0;
}
