#include "raylib.h"
#include "board.h"

int main()
{
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");
    SetTargetFPS(60);

    constexpr Vector2 boardDimensions{screenWidth, screenHeight};
    constexpr Vector2 boardPosition{(screenWidth - boardDimensions.x) / 2, (screenHeight - boardDimensions.y) / 2};
    Board Board(boardDimensions, boardPosition, PINK);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        Board.update();

        Board.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
