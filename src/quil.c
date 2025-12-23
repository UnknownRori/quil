#include <raylib.h>
#include <stddef.h>
#include <assert.h>

#include "quil.h"
#include "debug/input_debug.h"
#include "input/input.h"
#include "utils/raylib.h"

void QuilInit(Quil* q)
{
    assert(q != NULL);
    q->font_default = LoadFont("fonts/JetBrainsMonoNerdFontMono-Regular.ttf");
    SetTextureFilter(q->font_default.texture, TEXTURE_FILTER_POINT);
}

void QuilUpdate(Quil* q)
{
    assert(q != NULL);
    GetUserInput(&q->input);
}

void QuilDraw(Quil* q)
{
    assert(q != NULL);
    ClearBackground((Color) {25, 48, 48, 255});
    DrawTextPro(q->font_default, "696969", VEC2(0, 0), VEC2(0, 0), 0.0, 32, 1., WHITE);

    DebugDrawInput(&q->input);
    DrawFPS(0, GetScreenHeight());
}

void QuilUnload(Quil* q)
{
    assert(q != NULL);
    UnloadFont(q->font_default);
}
