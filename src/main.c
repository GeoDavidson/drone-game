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

    particle_t particles1[MAX_PARTICLES];
    for (int i = 0; i < MAX_PARTICLES - 1; i++) { 
        particles1[i].radius = 0.0f;
    }

    particle_t particles2[MAX_PARTICLES];
    for (int i = 0; i < MAX_PARTICLES - 1; i++) { 
        particles2[i].radius = 0.0f;
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
            if (particles1[i].radius <= 0.0f) {
                particles1[i].radius = abs(GetRandomValue(3, 5) * GetGamepadAxisMovement(0, 1));
                particles1[i].velocity.x = (GetRandomValue(0, 100) / 10.0f) * -forceX;
                particles1[i].velocity.y = (GetRandomValue(0, 100) / 10.0f) * -forceY;
                particles1[i].position.x = left.x;
                particles1[i].position.y = left.y;
                particles1[i].shrinkRate = GetRandomValue(1, 10) / 10.0f;
            } else {
                particles1[i].position.x += particles1[i].velocity.x;
                particles1[i].position.y += particles1[i].velocity.y;
                particles1[i].radius -= particles1[i].shrinkRate;
             }
        }

        for (int i = 0; i < MAX_PARTICLES - 1; i++) {             
            if (particles2[i].radius <= 0.0f) {
                particles2[i].radius = abs(GetRandomValue(3, 5) * GetGamepadAxisMovement(0, 1));
                particles2[i].velocity.x = (GetRandomValue(0, 100) / 10.0f) * -forceX;
                particles2[i].velocity.y = (GetRandomValue(0, 100) / 10.0f) * -forceY;
                particles2[i].position.x = right.x;
                particles2[i].position.y = right.y;
                particles2[i].shrinkRate = GetRandomValue(1, 10) / 10.0f;
            } else {
                particles2[i].position.x += particles2[i].velocity.x;
                particles2[i].position.y += particles2[i].velocity.y;
                particles2[i].radius -= particles2[i].shrinkRate;
             }
        }

        BeginDrawing();

        ClearBackground(WHITE);
        for (int i = 0; i < MAX_PARTICLES - 1; i++) { 
            DrawCircle(particles1[i].position.x + rect.width / 2 * cos(angle * DEG2RAD), particles1[i].position.y + left.height * sin(angle * DEG2RAD), particles1[i].radius, GREEN);
            DrawCircle(particles2[i].position.x - rect.width / 2 * cos(-angle * DEG2RAD), particles2[i].position.y + right.height * sin(-angle * DEG2RAD), particles2[i].radius, PURPLE);
        }

        DrawRectanglePro(normal, (Vector2){normal.width / 2, normal.height}, angle, RED);
        DrawRectanglePro(left, (Vector2){left.width + rect.width / 2, left.height / 2}, angle, BLUE);
        DrawRectanglePro(right, (Vector2){-rect.width / 2, right.height / 2}, angle, BLUE);
        DrawRectanglePro(rect, (Vector2){rect.width / 2, rect.height / 2}, angle, BLACK);


        DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
