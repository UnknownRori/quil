#pragma once

typedef enum InputModifier {
    INPUT_SHIFT = 0b0001,
    INPUT_CTRL  = 0b0010,
    INPUT_ALT   = 0b0100,
} InputModifier;

#define INPUT_MODIFIER_STATE(STATE, VALUE) (((STATE) & (VALUE)) != 0)

typedef struct UserInput {
    InputModifier modifier;
    char          key_press;
} UserInput;

int GetUserInput(UserInput*);
