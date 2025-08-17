#include "barrier.h"

Barrier::Barrier(const Vector2 dimensions, const Vector2 position, const Color color)
    : dimensions(dimensions),
      position(position),
      color(color)
{
}

void Barrier::setDimensions(const Vector2 newDimensions)
{
    this->dimensions = newDimensions;
}

Vector2 Barrier::getDimensions() const
{
    return dimensions;
}

void Barrier::setPosition(const Vector2 newPosition)
{
    this->position = newPosition;
}

Vector2 Barrier::getPosition() const
{
    return position;
}

void Barrier::setColor(const Color newColor)
{
    this->color = newColor;
}

Color Barrier::getColor() const
{
    return color;
}

Rectangle Barrier::getRectangle() const
{
    return Rectangle({position.x, position.y, dimensions.x, dimensions.y});
}

void Barrier::draw()
{
    DrawRectangleRec(getRectangle(), getColor());
}
