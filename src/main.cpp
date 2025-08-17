#include "raylib.h"
#include "board.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");
    SetTargetFPS(60);

    Vector2 boardDimensions{1000, 600};
    Vector2 boardPosition{(screenWidth - boardDimensions.x) / 2, (screenHeight - boardDimensions.y) / 2};
    Board Board(boardDimensions, boardPosition, PINK);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        Board.draw();

        // Draw text of the score
        Vector2 score = Board.getScore();
        DrawText(TextFormat("Score: %d - %d", (int)score.x, (int)score.y),
                 screenWidth / 2 - MeasureText(TextFormat("Score: %d - %d", (int)score.x, (int)score.y), 20) / 2,
                 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
