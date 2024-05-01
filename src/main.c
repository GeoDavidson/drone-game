#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define G 9.8
#define MASS 0.25
#define DRAG 0.99
#define THRUST 2

int main()
{
    const int winWidth = 800;
    const int winHeight = 450;

    InitWindow(winWidth, winHeight, "Basic Window");

    Rectangle rect = {winWidth / 2, winHeight / 2, 32, 8};
    Vector2 rectVel = {0.0f, 0.0f};

    float angle = 0.0f;
    float forceX = 0.0f;
    float forceY = 0.0f;

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        angle += GetGamepadAxisMovement(0, 2) * 10;
        forceX = -GetGamepadAxisMovement(0, 1) * THRUST * sin(angle * PI / 180);
        forceY = MASS * G + GetGamepadAxisMovement(0, 1) * THRUST * cos(angle * PI / 180);

        rectVel.x += forceX;
        rectVel.x *= DRAG;
        rect.x += rectVel.x;

        rectVel.y += forceY;
        rectVel.y *= DRAG;
        rect.y += rectVel.y;

        BeginDrawing();

        ClearBackground(WHITE);

        DrawRectanglePro(rect, (Vector2){rect.width / 2, rect.height / 2}, angle, BLACK);

        DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
