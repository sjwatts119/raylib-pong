#include "raylib.h"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello!", screenWidth / 2, screenHeight / 2, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}