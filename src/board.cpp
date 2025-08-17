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
      color(color),
      ball(Vector2{position.x + (position.x / 2), position.y + (position.y / 2)} , WHITE, 10)
{
    // Add top and bottom barriers
    barriers.push_back(std::make_unique<Barrier>(Vector2{dimensions.x, 10}, Vector2{position.x, position.y}));
    barriers.push_back(std::make_unique<Barrier>(Vector2{dimensions.x, 10}, Vector2{position.x, position.y + dimensions.y - 10}));

    // Add left and right paddles
    barriers.push_back(std::make_unique<Paddle>(Vector2{10, 100}, Vector2{position.x + 10, position.y + (dimensions.y / 2) - 50}));
    barriers.push_back(std::make_unique<Paddle>(Vector2{10, 100}, Vector2{position.x + dimensions.x - 20, position.y + (dimensions.y / 2) - 50}));
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

void Board::applyBallDeflections()
{
    for (auto &barrier : barriers)
    {
        std::optional<Side> collision = ball.getCollisionSide(barrier->getRectangle());

        if (!collision.has_value()) {
            continue;
        }

        ball.deflect(collision.value());
    }
}

void Board::draw()
{
    DrawRectangleRec(Board::getRectangle(), Board::getColor());

    for (auto &barrier : barriers)
    {
        barrier->draw();
    }

    ball.update();

    applyBallDeflections();

    ball.draw();
}
