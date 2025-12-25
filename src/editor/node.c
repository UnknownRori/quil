#include "node.h"
#include "rstb_da.h"
#include <assert.h>

void LineReset(Line* l)
{
    assert(l != NULL);
    l->items = NULL;
    l->count = 0;
    l->capacity = 0;
}
