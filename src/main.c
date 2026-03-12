#include "raylib.h"
#include "track.h"
#include "car.h"
#include "pure_pursuit.h"
#include "config.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "PID Visualization - Pure Pursuit Test");
    SetTargetFPS(144);

    Track track;
    Track_Init(&track);

    Car car;
    Car_Init(&car);
    Car_SetPose(&car, 300.0f, 300.0f, 0.0f);

    PurePursuit pp;
    PurePursuit_Init(&pp);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        /********************
         TRACK EDITOR INPUT
        ********************/
        Track_HandleInput(&track);

        /********************
         GLOBAL TEST INPUT
        ********************/
        if (IsKeyPressed(KEY_R))
        {
            Car_Reset(&car);
            Car_SetPose(&car, 300.0f, 300.0f, 0.0f);
            PurePursuit_Reset(&pp);
        }

        if (IsKeyPressed(KEY_UP))
        {
            PurePursuit_SetLookAhead(&pp, pp.lookAheadDistance + 5.0f);
        }

        if (IsKeyPressed(KEY_DOWN))
        {
            PurePursuit_SetLookAhead(&pp, pp.lookAheadDistance - 5.0f);
        }

        /********************
         CONTROLLER
        ********************/
        float throttle = 0.0f;
        float steeringInput = 0.0f;

        if (Track_IsReady(&track))
        {
            steeringInput = PurePursuit_GetSteeringInput(&pp, &car, &track);
            throttle = 1.0f;

            Car_Update(&car, throttle, steeringInput, dt);
        }

        /********************
         DRAW
        ********************/
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Track_Draw(&track);
        Track_DrawDebug(&track);

        DrawCar(&car, 40.0f, 22.0f, DARKGRAY);
        PurePursuit_DrawDebug(&pp);

        DrawText("TRACK EDITOR", 20, 20, 20, BLACK);
        DrawText("Left Click: add outer points", 20, 50, 18, DARKGRAY);
        DrawText("Right Click: add inner points", 20, 75, 18, DARKGRAY);
        DrawText("Use your existing track finalize controls", 20, 100, 18, DARKGRAY);

        DrawText("TEST CONTROLS", 20, 145, 20, BLACK);
        DrawText("R: reset car", 20, 175, 18, DARKGRAY);
        DrawText("UP / DOWN: change look-ahead distance", 20, 200, 18, DARKGRAY);

        DrawText(TextFormat("Look-ahead: %.2f", pp.lookAheadDistance), 20, 245, 18, BLUE);
        DrawText(TextFormat("Car position: (%.1f, %.1f)", car.x, car.y), 20, 270, 18, BLACK);
        DrawText(TextFormat("Heading: %.2f rad", car.heading), 20, 295, 18, BLACK);
        DrawText(TextFormat("Speed: %.2f", Car_GetSpeed(&car)), 20, 320, 18, BLACK);

        if (!Track_IsReady(&track))
        {
            DrawText("Track not ready yet.", 20, 360, 20, RED);
            DrawText("Create/finalize the track first so the car has a centerline to follow.", 20, 390, 18, RED);
        }
        else
        {
            DrawText("Pure pursuit active.", 20, 360, 20, DARKGREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}