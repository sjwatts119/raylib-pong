#include "board.h"

Board::Board(Vector2 dimensions, Vector2 position, Color color)
    : dimensions(dimensions),
      position(position),
      color(color),
      ball(position, WHITE, 10)
{
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
    return Rectangle{position.x - dimensions.x / 2, position.y - dimensions.y / 2, dimensions.x, dimensions.y};
}

void Board::draw()
{
    DrawRectangleRec(Board::getRectangle(), Board::getColor());

    ball.update();

    // Check all of our colliders for a collision.

    ball.draw();
}
