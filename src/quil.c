#include <raylib.h>
#include <stddef.h>
#include <assert.h>

#include "quil.h"
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
}

void QuilDraw(Quil* q)
{
    assert(q != NULL);
    ClearBackground((Color) {25, 48, 48, 255});
    DrawTextPro(q->font_default, "696969", VEC2(0, 0), VEC2(0, 0), 0.0, 32, 1., WHITE);
}

void QuilUnload(Quil* q)
{
    assert(q != NULL);
    UnloadFont(q->font_default);
}
