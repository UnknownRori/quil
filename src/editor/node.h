#pragma once

#include <rstb_arena.h>
#include <rstb_da.h>

rstb_da_decl(char, Line);
rstb_da_decl(Line, LineChunk);

void LineReset(Line*);
