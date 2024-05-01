#include <stdio.h>
#include <math.h>
#include "raylib.h"

int main()
{
    const int winWidth = 800;
    const int winHeight = 450;

    InitWindow(winWidth, winHeight, "Basic Window");

    Rectangle rect = {winWidth / 2, winHeight / 2, 96, 16};
    Vector2 rectVel = {0.0f, 0.0f};

    float force = 0.0f;
    float gravity = 0.0f;
    float angle = 0.0f;
    float forceX = 0.0f;
    float forceY = 0.0f;

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        angle += GetGamepadAxisMovement(0, 2) * 10;

        forceY = 9.8 / 15 + (GetGamepadAxisMovement(0, 1)) * 2 * cos(angle * PI / 180);
        forceX = -(GetGamepadAxisMovement(0, 1)) * 2 * sin(angle * PI / 180);

        rectVel.x += forceX;
        rect.x += rectVel.x;

        rectVel.y += forceY;
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
