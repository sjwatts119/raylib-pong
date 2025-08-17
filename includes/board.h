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

    Vector2 score = {0, 0};

    float barrierWidth = 10.0f;

    float paddleInset = 20.0f;
    float paddleHeight = 100.0f;

    std::optional<Ball> ball;
    std::vector<std::unique_ptr<Barrier>> barriers;

public:
    explicit Board(Vector2 dimensions, Vector2 position, Color color = WHITE);

    void setDimensions(Vector2 dimensions);

    Vector2 getDimensions();

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setColor(Color color);

    Color getColor();

    void setScore(Vector2 score);

    Vector2 getScore();

    Rectangle getRectangle();

    Rectangle getPlayAreaRectangle() const;

    bool hasWinningSide();

    std::optional<Side> getWinningSide();

    void initBarriers();

    void initBall();

    void iterateScore(Side side);

    void reset();

    void applyBallDeflections();

    void draw();
};

#endif //RAYLIBTEMPLATE_BOARD_H
