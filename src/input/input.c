#include <raylib.h>
#include <stddef.h>
#include <assert.h>

#include "input.h"
#include "utils/utils.h"

struct {
    int type;
    int result;
} modifier[] = {
    {KEY_LEFT_CONTROL, INPUT_CTRL},
    {KEY_RIGHT_CONTROL, INPUT_CTRL},
    {KEY_LEFT_SHIFT, INPUT_SHIFT},
    {KEY_RIGHT_SHIFT, INPUT_SHIFT},
    {KEY_LEFT_ALT, INPUT_SHIFT},
    {KEY_RIGHT_ALT, INPUT_ALT},
};

int GetUserInput(UserInput* in)
{
    assert(in != NULL);
    in->key_press = GetCharPressed();
    in->modifier = 0;
    for (size_t i = 0; i < ARRAY_LEN(modifier); i++) {
        if (IsKeyDown(modifier[i].type)) {
            in->modifier |= modifier[i].result;
        }
    }
    return 0;
}
