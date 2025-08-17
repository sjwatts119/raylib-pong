#ifndef RAYLIBTEMPLATE_BOARD_H
#define RAYLIBTEMPLATE_BOARD_H
#include <vector>

#include "ball.h"
#include "barrier.h"
#include "paddle.h"
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
    float paddleWidth = 20.0f;

    Scoreboard scoreboard;
    Ball ball;
    std::vector<Barrier> barriers;
    std::vector<Paddle> paddles;

public:
    explicit Board(Vector2 dimensions, Vector2 position, Color color = WHITE);

    void setDimensions(Vector2 newDimensions);

    [[nodiscard]] Vector2 getDimensions() const;

    void setPosition(Vector2 newPosition);

    [[nodiscard]] Vector2 getPosition() const;

    void setColor(Color newColor);

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] Rectangle getGameRectangle() const;

    [[nodiscard]] Rectangle getPlayAreaRectangle() const;

    [[nodiscard]] bool hasWinningSide() const;

    [[nodiscard]] std::optional<Side> getWinningSide() const;

    [[nodiscard]] std::vector<std::unique_ptr<Barrier>> getColliders() const;

    void initColliders();

    void reset();

    void applyPaddleMovements();

    void applyBallDeflections();

    void update();

    void draw() const;

private:
    [[nodiscard]] Ball createInitialBall() const;

    [[nodiscard]] Scoreboard createInitialScoreboard() const;

    void pushBallOutOfCollision(const Rectangle& rect, Side collisionSide);
};

#endif //RAYLIBTEMPLATE_BOARD_H
