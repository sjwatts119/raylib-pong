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
}

Rectangle Board::getPlayAreaRectangle() const
{
    return Rectangle{
        position.x,
        position.y + barrierWidth,
        dimensions.x,
        dimensions.y - (2 * barrierWidth)
    };
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

Rectangle Board::getRectangle()
{
    return Rectangle{position.x, position.y, dimensions.x, dimensions.y};
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
    for (auto &barrier: barriers) {
        std::optional<Side> collision = ball->getCollisionSide(barrier->getRectangle());

        if (!collision.has_value()) {
            continue;
        }

        ball->deflect(collision.value());
    }
}

void Board::initBarriers()
{
    // Add top and bottom barriers
    barriers.push_back(std::make_unique<Barrier>(
        Vector2{dimensions.x, barrierWidth},
        Vector2{position.x, position.y}
    ));
    barriers.push_back(std::make_unique<Barrier>(
        Vector2{dimensions.x, barrierWidth},
        Vector2{position.x, position.y + dimensions.y - barrierWidth}
    ));

    // Add left and right paddles
    barriers.push_back(std::make_unique<Paddle>(
        Vector2{barrierWidth, paddleHeight},
        Vector2{position.x + paddleInset, position.y + (dimensions.y / 2) - (paddleHeight / 2)},
        getPlayAreaRectangle()
    ));
    barriers.push_back(std::make_unique<Paddle>(
        Vector2{barrierWidth, paddleHeight},
        Vector2{
            position.x + dimensions.x - paddleInset - barrierWidth, position.y + (dimensions.y / 2) - (paddleHeight / 2)
        },
        getPlayAreaRectangle()
    ));
}

void Board::initBall()
{
    Vector2 playAreaCenter = {
        position.x + (dimensions.x / 2),
        position.y + (dimensions.y / 2)
    };

    ball = Ball(playAreaCenter, WHITE, 10);
}

void Board::reset()
{
    initBall();
}

void Board::draw()
{
    DrawRectangleRec(getRectangle(), getColor());

    for (const auto &barrier: barriers) {
        barrier->draw();
    }

    ball->update();

    applyBallDeflections();

    std::optional<Side> winningSide = getWinningSide();
    if (winningSide.has_value()) {
        reset();
    }

    ball->draw();
}
