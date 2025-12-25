#include <assert.h>

#include "buffer.h"
#include "editor/editor.h"
#include "rendering/cursor_carret.h"
#include "utils/raylib.h"
#include "raylib.h"

void RenderEditorBuffer(Font f, Editor* e, Vector2 pos)
{
    assert(e != NULL);
    static size_t font_size = 28;
    static size_t spacing = 0;
    size_t total = EditorGetTotalLine(e);
    Vector2 temp = pos;
    for (size_t i = 0; i < total; i++)
    {
        Line* line = EditorGetLine(e, i);

        if (e->line_pos == i) {
            DrawRectangleRec(RECT(0, pos.y, GetScreenWidth(), f.baseSize - spacing), ColorAlpha(GRAY, 0.2));
        }

        const char* line_num = TextFormat("%4zu", i + 1);
        Vector2 measure = MeasureTextEx(f, line_num, font_size, spacing);
        DrawTextEx(f, line_num, pos, font_size, spacing, GRAY);
        pos.x += measure.x;

        DrawLineEx(VEC2(pos.x + 4, pos.y), VEC2(pos.x + 4, pos.y + measure.y), 1., GRAY);

        if (line->count == 0) {
            measure = MeasureTextEx(f, " ", font_size, spacing);
        } else {
            DrawTextEx(f, line->items, OFFSET_VEC2(pos, 8, 0), font_size, spacing, WHITE);
            measure = MeasureTextEx(f, line->items, font_size, spacing);
        }

        if (e->line_pos == i) {
            const char* chop = NULL;
            if (e->column_pos > line->count - 1) {
                chop = TextFormat(" %.*s", e->column_pos + 1, line->items);
            } else if (line->count == 0) {
                chop = " ";
            } else {
                chop = TextFormat("%.*s", e->column_pos + 1, line->items);
            }
            Vector2 measure = MeasureTextEx(f, chop, font_size, spacing);
            DrawCursorCarret(VEC2(14, measure.y), VEC2(pos.x + measure.x - 4, pos.y));
        }

        pos.x = temp.x;
        pos.y += measure.y;
    }
}
