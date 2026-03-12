#include "raylib.h"
#include "track.h"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "PID Track Editor");
    SetTargetFPS(144);

    Track track;
    Track_Init(&track);

    while (!WindowShouldClose()) {
        Track_HandleInput(&track);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Track_Draw(&track);
        Track_DrawDebug(&track);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}