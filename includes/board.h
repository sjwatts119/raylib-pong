#ifndef RAYLIBTEMPLATE_BOARD_H
#define RAYLIBTEMPLATE_BOARD_H
#include <vector>

#include "ball.h"
#include "barrier.h"
#include "raylib.h"
#include "scoreboard.h"

class Board
{
private:
    Vector2 dimensions;
    Vector2 position;
    Color color = WHITE;

    float barrierWidth = 10.0f;

    float paddleInset = 20.0f;
    float paddleHeight = 100.0f;

    std::optional<Scoreboard> scoreboard;
    std::optional<Ball> ball;
    std::vector<std::unique_ptr<Barrier> > barriers;

public:
    explicit Board(Vector2 dimensions, Vector2 position, Color color = WHITE);

    void setDimensions(Vector2 dimensions);

    Vector2 getDimensions();

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setColor(Color color);

    Color getColor();

    Rectangle getGameRectangle() const;

    Rectangle getPlayAreaRectangle() const;

    bool hasWinningSide();

    std::optional<Side> getWinningSide();

    void initBarriers();

    void initBall();

    void initScoreboard();

    void reset();

    void applyBallDeflections();

    void pushBallOutOfCollision(const Rectangle& rect, Side collisionSide);

    void update();

    void draw();
};

#endif //RAYLIBTEMPLATE_BOARD_H
