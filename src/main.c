#include <raylib.h>

#include "app.h"
#include "globals.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static void UpdateGame()
{
    AppUpdate();
}


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
    SetTargetFPS(GAME_TARGET_FPS);
    InitAudioDevice();
    AppInit();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateGame, 0, 1);
#else
    while (!WindowShouldClose()) {
        if (AppIsExit()) break;
        UpdateGame();
    }
#endif

    AppDestroy();

    return 0;
}
