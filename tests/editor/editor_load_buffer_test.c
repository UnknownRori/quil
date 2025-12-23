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
    assert(e.line != NULL && "Line must be initialized");
    assert(e.line->next != NULL && "Line.next must be initialized");
    assert(e.line->next->next != NULL && "Line.next.next must be initialized");

    Line* l = e.line;
    assert(strcmp(l->buffer, "Agus\n") && "1st line must be Agus");

    l = l->next;
    assert(strcmp(l->buffer, "Pamungkas\n") && "2nd line must Pamungkas");

    l = l->next;
    fprintf(stderr, "%p", l->buffer);
    assert(strcmp(l->buffer, "Bambang") && "3rd line must Bambang");

    EditorUnload(&e);

    return 0;
}
