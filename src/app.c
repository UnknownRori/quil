#include <raylib.h>
#include <stdbool.h>

#include "app.h"
#include "globals.h"
#include "quil.h"

static Quil q;

void AppInit()
{
    ChangeDirectory(ASSETS_PATH);
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
