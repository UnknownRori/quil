#include <raylib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "quil.h"
#include "debug/input_debug.h"
#include "editor/editor.h"
#include "input/input.h"
#include "rendering/buffer.h"
#include "utils/raylib.h"

const char* contents = "Agus\nPamungkas\nBambang";

void QuilInit(Quil* q)
{
    assert(q != NULL);

    q->font_default = LoadFont("fonts/JetBrainsMonoNerdFontMono-Regular.ttf");
    SetTextureFilter(q->font_default.texture, TEXTURE_FILTER_TRILINEAR);

    EditorInit(&q->e);
    EditorLoadBuffer(&q->e, contents, strlen(contents));
}

void QuilUpdate(Quil* q)
{
    assert(q != NULL);
    GetUserInput(&q->input);

    // TODO : Refactor this control line
    if (INPUT_MODIFIER_STATE(q->input.nav, NAV_UP)) {
        EditorIncSelectedLine(&q->e, -1);
    }
    if (INPUT_MODIFIER_STATE(q->input.nav, NAV_DOWN)) {
        EditorIncSelectedLine(&q->e, 1);
    }

    if (INPUT_MODIFIER_STATE(q->input.nav, NAV_RIGHT)) {
        EditorIncSelectedColumn(&q->e, 1);
    }
    if (INPUT_MODIFIER_STATE(q->input.nav, NAV_LEFT)) {
        EditorIncSelectedColumn(&q->e, -1);
    }

    if ((q->input.key_press != 0) && ((q->input.modifier == 0) || (INPUT_MODIFIER_STATE(q->input.modifier, INPUT_SHIFT)))) {
        EditorAppendCharOnCurrentCursor(&q->e, q->input.key_press);
    }

    if (INPUT_MODIFIER_STATE(q->input.modifier, INPUT_CTRL) &&
        INPUT_MODIFIER_STATE(q->input.modifier, INPUT_SHIFT) &&
        IsKeyPressed(KEY_Z)) {
        EditorRedo(&q->e);
        TraceLog(LOG_INFO, "CTRL + SHIFT + Z pressed - Redo");
    } else if (INPUT_MODIFIER_STATE(q->input.modifier, INPUT_CTRL) && 
        IsKeyPressed(KEY_Z)) {
        EditorUndo(&q->e);
        TraceLog(LOG_INFO, "CTRL + Z pressed - Undo");
    }
    if (INPUT_MODIFIER_STATE(q->input.control, CONTROL_DELETE)) {
        EditorRemoveCharOnCurrentCursor(&q->e);
    }
    if (INPUT_MODIFIER_STATE(q->input.control, CONTROL_NEW_LINE)) {
        EditorAddNewLineOnCurrentCursor(&q->e);
    }
    if (INPUT_MODIFIER_STATE(q->input.control, CONTROL_START_LINE)) {
        EditorSetSelectedColumnBeginning(&q->e);
    }
    if (INPUT_MODIFIER_STATE(q->input.control, CONTROL_END_LINE)) {
        EditorSetSelectedColumnEnd(&q->e);
    }
}

void QuilDraw(Quil* q)
{
    assert(q != NULL);
    ClearBackground((Color) {25, 48, 48, 255});
    RenderEditorBuffer(q->font_default ,&q->e, VEC2(0, 0));

    DebugDraw(&q->input, &q->e);
    DrawFPS(0, GetScreenHeight());
}

void QuilUnload(Quil* q)
{
    assert(q != NULL);

    UnloadFont(q->font_default);
    EditorUnload(&q->e);
}
