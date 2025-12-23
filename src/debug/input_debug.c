#include "input_debug.h"
#include "raylib.h"

void DebugDrawInput(const UserInput* in)
{
    DrawText(TextFormat("pressed: %c", in->key_press), 0, GetScreenHeight() - 32, 16, WHITE);
    DrawText(TextFormat("modifier: %d", in->modifier), 0, GetScreenHeight() - 16, 16, WHITE);
}
