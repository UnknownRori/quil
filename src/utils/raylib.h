#pragma once

#include <raylib.h>

#define VEC2(X, Y) (Vector2) {(X), (Y)}
#define VEC2_ZERO (Vector2) {0, 0}
#define OFFSET_VEC2(VEC2, X, Y) (Vector2) {.x = (VEC2).x + (X), .y = (VEC2).y + (Y)}

#define RECT(X, Y, W, H) (Rectangle) {(X), (Y), (W), (H)}
#define RECT_FROM_VEC2(VEC2, W, H) (Rectangle) {.x = (VEC2).x, .y = (VEC2).y, .width = (W), .height = (H)}
