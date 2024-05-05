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

    Rectangle body = {winWidth / 2, winHeight / 2, 32, 8};
    Rectangle left = {body.x, body.y, 4, 12};
    Rectangle right = {body.x, body.y, 4, 12};

    Rectangle box = {winWidth / 2, winHeight - 64, 96, 96};
    Rectangle horizontal = {winWidth / 2, winHeight - 64, 96, 2};
    Rectangle vertical = {winWidth / 2, winHeight - 64, 2, 96};

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
        body.x += rectVel.x;

        rectVel.y += forceY + G;
        rectVel.y *= DRAG;
        body.y += rectVel.y;

        left.x = body.x;
        left.y = body.y;

        right.x = body.x;
        right.y = body.y;

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
            DrawCircle(particles1[i].position.x + right.width / 2 + body.width / 2 * cos(angle * DEG2RAD), particles1[i].position.y + left.height * sin(angle * DEG2RAD), particles1[i].radius, GREEN);
            DrawCircle(particles2[i].position.x - left.width / 2 - body.width / 2 * cos(-angle * DEG2RAD), particles2[i].position.y + right.height * sin(-angle * DEG2RAD), particles2[i].radius, PURPLE);
        }

        DrawRectanglePro(left, (Vector2){left.width + body.width / 2, left.height / 2}, angle, PURPLE);
        DrawRectanglePro(right, (Vector2){-body.width / 2, right.height / 2}, angle, GREEN);
        DrawRectanglePro(body, (Vector2){body.width / 2, body.height / 2}, angle, BLACK);

        DrawRectanglePro(box, (Vector2){box.width / 2, box.height / 2}, 0.0f, (Color){80, 80, 80, 80});
        DrawRectanglePro(vertical, (Vector2){vertical.width / 2, vertical.height / 2}, 0.0f, (Color){135, 135, 135, 135});
        DrawRectanglePro(horizontal, (Vector2){horizontal.width / 2, horizontal.height / 2}, 0.0f, (Color){135, 135, 135, 135});
        DrawCircle(box.x + GetGamepadAxisMovement(0, 2) * 48, box.y + GetGamepadAxisMovement(0, 1) * 48, 6, (Color){135, 135, 135, 135});

        DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
