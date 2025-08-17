#ifndef RAYLIBTEMPLATE_BOARD_H
#define RAYLIBTEMPLATE_BOARD_H
#include <vector>

#include "ball.h"
#include "barrier.h"
#include "raylib.h"

class Board
{
private:
    Vector2 dimensions;
    Vector2 position;
    Color color = WHITE;

    Ball ball;
    std::vector<std::unique_ptr<Barrier>> barriers;

public:
    explicit Board(Vector2 dimensions, Vector2 position, Color color = WHITE);

    void setDimensions(Vector2 dimensions);

    Vector2 getDimensions();

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setColor(Color color);

    Color getColor();

    Rectangle getRectangle();

    void applyBallDeflections();

    void draw();
};

#endif //RAYLIBTEMPLATE_BOARD_H
