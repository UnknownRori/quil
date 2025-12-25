#include <assert.h>
#include <stddef.h>

#include "time_travel.h"
#include <rstb_da.h>

void        UndoStackReset      (UndoStack* s)
{
    assert(s != NULL);
    rstb_da_reset(s);
    s->top = 0;
}

void        UndoStackFree       (UndoStack* s)
{
    assert(s != NULL);
    rstb_da_free(s);
    s->top = 0;
}

void        UndoStackPush       (UndoStack* s, EditorCmd c)
{
    assert(s != NULL);
    rstb_da_reserve(s, s->count + 1);
    s->items[s->top] = c;
    s->count += 1;
    s->top++;
}

void        UndoStackNext       (UndoStack* s)
{
    assert(s != NULL);
    s->top++;
}
void        UndoStackPrev       (UndoStack* s)
{
    assert(s != NULL);
    s->top--;
}

EditorCmd   UndoStackCurrent    (UndoStack* s)
{
    assert(s != NULL);
    return s->items[s->top - 1];
}
