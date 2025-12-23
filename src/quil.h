#pragma once

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

#include "editor/editor.h"
#include "input/input.h"

typedef struct Quil {
    Font       font_default;

    UserInput  input;
    bool       is_quit;

    Editor     e;
} Quil;

void QuilInit(Quil*);
void QuilUpdate(Quil*);
void QuilDraw(Quil*);
void QuilUnload(Quil*);
