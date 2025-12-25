#include <raylib.h>

#include "cursor_carret.h"
#include "utils/raylib.h"

void DrawCursorCarret(Vector2 size, Vector2 pos)
{
    DrawRectangleRec(RECT_FROM_VEC22(pos, size), ColorAlpha(WHITE, 0.5));
}
