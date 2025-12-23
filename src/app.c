#include <raylib.h>
#include <stdbool.h>

#include "app.h"
#include "globals.h"
#include "quil.h"

static Quil q;

void AppInit()
{
    ChangeDirectory(ASSETS_PATH);
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    QuilInit(&q);
}

void AppUpdate()
{
    QuilUpdate(&q);

    BeginDrawing(); {
        QuilDraw(&q);
    }; EndDrawing();
}

void AppDestroy()
{
    QuilUnload(&q);
}

bool AppIsExit() { return q.is_quit; }

void AppExit() { q.is_quit = true; }
