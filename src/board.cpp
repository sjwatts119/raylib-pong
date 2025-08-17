#include "board.h"
#include <vector>
#include "barrier.h"
#include "ball.h"
#include "paddle.h"
#include "raylib.h"
#include "side.h"

Board::Board(Vector2 dimensions, Vector2 position, Color color)
    : dimensions(dimensions),
      position(position),
      color(color)
{
    initBarriers();
    initBall();
    initScoreboard();
}

void Board::setDimensions(Vector2 dimensions)
{
    this->dimensions = dimensions;
}

Vector2 Board::getDimensions()
{
    return dimensions;
}

void Board::setPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Board::getPosition()
{
    return position;
}

void Board::setColor(Color color)
{
    this->color = color;
}

Color Board::getColor()
{
    return color;
}

Rectangle Board::getGameRectangle() const
{
    return Rectangle{position.x, position.y, dimensions.x, dimensions.y - 100};
}

Rectangle Board::getPlayAreaRectangle() const
{
    auto [x, y, width, height] = getGameRectangle();
    return Rectangle{
        x,
        y + barrierWidth,
        width,
        height - (2 * barrierWidth)
    };
}

bool Board::hasWinningSide()
{
    return getWinningSide().has_value();
}

std::optional<Side> Board::getWinningSide()
{
    if (CheckCollisionCircleRec(ball->getPosition(), ball->getRadius(), getPlayAreaRectangle())) {
        return std::nullopt;
    }

    return ball->getPosition().x < position.x ? Side::LEFT : Side::RIGHT;
}

void Board::applyBallDeflections()
{
    for (const auto &barrier: barriers) {
        std::optional<Side> collisionSide = ball->getCollisionSide(barrier->getRectangle());

        if (!collisionSide.has_value()) {
            continue;
        }

        // Deflect the ball
        ball->deflect(collisionSide.value());

        pushBallOutOfCollision(barrier->getRectangle(), collisionSide.value());
    }
}

void Board::pushBallOutOfCollision(const Rectangle& rect, Side collisionSide)
{
    Vector2 ballPos = ball->getPosition();
    int radius = ball->getRadius();
    int buffer = ball->getSpeed() + 1;

    switch (collisionSide) {
        case Side::LEFT:
            ballPos.x = rect.x - radius - buffer;
            break;
        case Side::RIGHT:
            ballPos.x = rect.x + rect.width + radius + buffer;
            break;
        case Side::TOP:
            ballPos.y = rect.y - radius - buffer;
            break;
        case Side::BOTTOM:
            ballPos.y = rect.y + rect.height + radius + buffer;
            break;
    }

    ball->setPosition(ballPos);
}

void Board::initBarriers()
{
    Rectangle gameRect = getGameRectangle();

    // Add top and bottom barriers
    barriers.push_back(std::make_unique<Barrier>(
        Vector2{gameRect.width, barrierWidth},
        Vector2{gameRect.x, gameRect.y}
    ));
    barriers.push_back(std::make_unique<Barrier>(
        Vector2{gameRect.width, barrierWidth},
        Vector2{gameRect.x, gameRect.y + gameRect.height - barrierWidth}
    ));

    // Add left and right paddles
    barriers.push_back(std::make_unique<Paddle>(
        Vector2{barrierWidth, paddleHeight},
        Vector2{gameRect.x + paddleInset, gameRect.y + (gameRect.height / 2) - (paddleHeight / 2)},
        getPlayAreaRectangle()
    ));
    barriers.push_back(std::make_unique<Paddle>(
        Vector2{barrierWidth, paddleHeight},
        Vector2{
            gameRect.x + gameRect.width - paddleInset - barrierWidth,
            gameRect.y + (gameRect.height / 2) - (paddleHeight / 2)
        },
        getPlayAreaRectangle()
    ));
}

void Board::initBall()
{
    Rectangle gameRect = getGameRectangle();
    Vector2 playAreaCenter = {
        gameRect.x + (gameRect.width / 2),
        gameRect.y + (gameRect.height / 2)
    };

    ball = Ball(playAreaCenter, WHITE, 10);
}

void Board::initScoreboard()
{
    Rectangle gameRect = getGameRectangle();

    scoreboard = Scoreboard(
        Vector2{position.x, gameRect.y + gameRect.height},
        Vector2{dimensions.x, std::abs(gameRect.height - dimensions.y)}
    );
}

void Board::reset()
{
    initBall();
}

void Board::update()
{
    ball->update();

    applyBallDeflections();

    if (const std::optional<Side> winningSide = getWinningSide()) {
        scoreboard->iterateScore(winningSide.value());

        reset();
    }
}

void Board::draw()
{
    DrawRectangleRec(getGameRectangle(), getColor());

    for (const auto &barrier: barriers) {
        barrier->draw();
    }

    ball->draw();

    scoreboard->draw();
}
