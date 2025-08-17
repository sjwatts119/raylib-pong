#include "barrier.h"

Barrier::Barrier(Vector2 dimensions, Vector2 position, Color color)
    : dimensions(dimensions),
      position(position),
      color(color)
{
}

void Barrier::setDimensions(Vector2 dimensions)
{
    this->dimensions = dimensions;
}

Vector2 Barrier::getDimensions()
{
    return dimensions;
}

void Barrier::setPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Barrier::getPosition()
{
    return position;
}

void Barrier::setColor(Color color)
{
    this->color = color;
}

Color Barrier::getColor()
{
    return color;
}

Rectangle Barrier::getRectangle()
{
    return Rectangle({position.x, position.y, dimensions.x, dimensions.y});
}

void Barrier::draw()
{
    DrawRectangleRec(Barrier::getRectangle(), Barrier::getColor());
}
