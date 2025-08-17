#include "raylib.h"
#include "board.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");
    SetTargetFPS(60);

    Vector2 boardDimensions{screenWidth / 2, screenHeight / 2};
    Vector2 boardPosition{(screenWidth - boardDimensions.x) / 2, (screenHeight - boardDimensions.y) / 2};
    Board Board(boardDimensions, boardPosition, PINK);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Board.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
