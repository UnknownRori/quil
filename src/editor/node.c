#include "node.h"
#include <assert.h>

Line* LineInit(rstb_arena* a)
{
    Line* l = rstb_arena_alloc(a, sizeof(Line));
    memset(l, 0, sizeof(Line));
    return l;
}
