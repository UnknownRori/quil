#include "input_debug.h"
#include "raylib.h"

void DebugDrawInput(const UserInput* in)
{
    DrawText(TextFormat("pressed: %c", in->key_press), 0, GetScreenHeight() - 48, 16, WHITE);
    DrawText(TextFormat("nav: %d", in->nav), 0, GetScreenHeight() - 32, 16, WHITE);
    DrawText(TextFormat("modifier: %d", in->modifier), 0, GetScreenHeight() - 16, 16, WHITE);
}

void DebugDrawEditor(const Editor* e)
{
    DrawText(TextFormat("pos: %d:%d", e->line_pos, e->column_pos), 0, GetScreenHeight() - 64, 16, WHITE);
}

void DebugDraw(const UserInput* in, Editor* e)
{
    DebugDrawInput(in);
    DebugDrawEditor(e);
}
