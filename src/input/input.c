#include <raylib.h>
#include <stddef.h>
#include <assert.h>

#include "input.h"
#include "utils/utils.h"

static struct {
    int type;
    int result;
} modifier[] = {
    {KEY_LEFT_CONTROL, INPUT_CTRL},
    {KEY_RIGHT_CONTROL, INPUT_CTRL},
    {KEY_LEFT_SHIFT, INPUT_SHIFT},
    {KEY_RIGHT_SHIFT, INPUT_SHIFT},
    {KEY_LEFT_ALT, INPUT_ALT},
    {KEY_RIGHT_ALT, INPUT_ALT},
};

static struct {
    int type;
    int result;
} navigation[] = {
    {KEY_UP, NAV_UP},
    {KEY_LEFT, NAV_LEFT},
    {KEY_RIGHT, NAV_RIGHT},
    {KEY_DOWN, NAV_DOWN},
};

static struct {
    int type;
    int result;
} controls[] = {
    {KEY_ENTER, CONTROL_NEW_LINE},
    {KEY_BACKSPACE, CONTROL_DELETE},
    {KEY_HOME, CONTROL_START_LINE},
    {KEY_END, CONTROL_END_LINE},
};

int GetUserInput(UserInput* in)
{
    assert(in != NULL);
    in->key_press = GetCharPressed();
    in->modifier  = 0;
    in->control   = 0;
    in->nav       = 0;
    for (size_t i = 0; i < ARRAY_LEN(modifier); i++) {
        if (IsKeyDown(modifier[i].type)) {
            in->modifier |= modifier[i].result;
        }
    }

    for (size_t i = 0; i < ARRAY_LEN(navigation); i++) {
        if (IsKeyPressed(navigation[i].type)) {
            in->nav |= navigation[i].result;
        }
    }

    for (size_t i = 0; i < ARRAY_LEN(controls); i++) {
        if (IsKeyPressed(controls[i].type)) {
            in->control |= controls[i].result;
        }
    }

    return 0;
}
