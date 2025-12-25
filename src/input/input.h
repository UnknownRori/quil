#pragma once

typedef enum InputModifier {
    INPUT_SHIFT = 0b0001,
    INPUT_CTRL  = 0b0010,
    INPUT_ALT   = 0b0100,
} InputModifier;

typedef enum Navigation {
    NAV_UP    = 0b0001,
    NAV_DOWN  = 0b0010,
    NAV_RIGHT = 0b0100,
    NAV_LEFT  = 0b1000,
} Navigation;

// TODO : Do I really need bit mask for this?
typedef enum ControlLineKey {
    CONTROL_NEW_LINE    = 0b0001,
    CONTROL_DELETE      = 0b0010,
    CONTROL_START_LINE  = 0b0100,
    CONTROL_END_LINE    = 0b1000,
} ControlLineKey;

#define INPUT_MODIFIER_STATE(STATE, VALUE) (((STATE) & (VALUE)) != 0)

typedef struct UserInput {
    InputModifier   modifier;
    Navigation      nav;
    ControlLineKey  control;
    char            key_press;
} UserInput;

int GetUserInput(UserInput*);
