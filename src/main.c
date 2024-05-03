#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define G 0.45
#define DRAG 0.984
#define THRUST 2

#define MAX_PARTICLES 200

typedef struct particle {
    float radius;
    Vector2 velocity;
    Vector2 position;
    float shrinkRate;
} particle_t;

// float min(float a, float b) {
//     return (a < b) ? a : b;
// }

float max(float a, float b) {
    return (a > b) ? a : b;
}

int main() {
    const int winWidth = 800;
    const int winHeight = 450;

    InitWindow(winWidth, winHeight, "Drone Game");

    Rectangle rect = {winWidth / 2, winHeight / 2, 32, 8};
    Rectangle left = {rect.x, rect.y, 4, 12};
    Rectangle normal = {rect.x, rect.y, 4, 24};
    Rectangle right = {rect.x, rect.y, 4, 12};

    float force = 0.0f;
    float angle = 0.0f;
    float forceX = 0.0f;
    float forceY = 0.0f;
    Vector2 rectVel = {0.0f, 0.0f};

    particle_t particles[MAX_PARTICLES];
    for (int i = 0; i < MAX_PARTICLES - 1; i++) { 
        particles[i].radius = 0.0f;
    }

    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        force = GetGamepadAxisMovement(0, 1) * THRUST;
        angle += GetGamepadAxisMovement(0, 2) * 10;
        forceX = -force * sin(angle * PI / 180);
        forceY = force * cos(angle * PI / 180);

        rectVel.x += forceX;
        rectVel.x *= DRAG;
        rect.x += rectVel.x;

        rectVel.y += forceY + G;
        rectVel.y *= DRAG;
        rect.y += rectVel.y;

        left.x = rect.x;
        left.y = rect.y;

        normal.x = rect.x;
        normal.y = rect.y;

        right.x = rect.x;
        right.y = rect.y;

        for (int i = 0; i < MAX_PARTICLES - 1; i++) {             
            if (particles[i].radius <= 0.0f) {
                if (GetGamepadAxisMovement(0, 1) != 0.0f) {
                    particles[i].radius = abs(GetRandomValue(3, 5) * max(0.55, abs(GetGamepadAxisMovement(0, 1))));
                } else {
                    particles[i].radius = abs(GetRandomValue(3, 5) * GetGamepadAxisMovement(0, 1));
                }
                particles[i].velocity.x = (GetRandomValue(-30, 30) / 10.0f);
                particles[i].velocity.y = (GetRandomValue(0, 100) / 10.0f);
                particles[i].position.x = rect.x;
                particles[i].position.y = rect.y;
                particles[i].shrinkRate = GetRandomValue(1, 10) / 10.0f;
            } else {
                particles[i].position.x += particles[i].velocity.x;
                particles[i].position.y += particles[i].velocity.y;
                particles[i].radius -= particles[i].shrinkRate;
             }
        }

        BeginDrawing();

        ClearBackground(WHITE);

        DrawRectanglePro(normal, (Vector2){normal.width / 2, normal.height}, angle, RED);
        DrawRectanglePro(left, (Vector2){left.width + rect.width / 2, left.height / 2}, angle, BLUE);
        DrawRectanglePro(right, (Vector2){-rect.width / 2, right.height / 2}, angle, BLUE);
        DrawRectanglePro(rect, (Vector2){rect.width / 2, rect.height / 2}, angle, BLACK);

        for (int i = 0; i < MAX_PARTICLES - 1; i++) { 
            DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, ORANGE);
        }

        DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
