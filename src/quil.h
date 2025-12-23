#pragma once

#include <raylib.h>
#include <stdbool.h>

typedef struct Quil {
    Font font_default;

    bool is_quit;
} Quil;

void QuilInit(Quil*);
void QuilUpdate(Quil*);
void QuilDraw(Quil*);
void QuilUnload(Quil*);
