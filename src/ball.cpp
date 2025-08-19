#include "ball.h"

#include <algorithm>

#include "side.h"

Ball::Ball(const Vector2 position, const Color color, const float radius)
    : position(position), color(color), radius(radius)
{
    // Set a random initial movement direction
    movement.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
    movement.y = GetRandomValue(0, 1) == 0 ? -1 : 1;
}

void Ball::setPosition(const Vector2 newPosition)
{
    this->position = newPosition;
}

Vector2 Ball::getPosition() const
{
    return position;
}

void Ball::setMovement(const Vector2 newMovement)
{
    this->movement = newMovement;
}

Vector2 Ball::getMovement() const
{
    return movement;
}

void Ball::setColor(const Color newColor)
{
    this->color = newColor;
}

Color Ball::getColor() const
{
    return color;
}

void Ball::setRadius(const float newRadius)
{
    this->radius = newRadius;
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::setSpeed(const float newSpeed)
{
    this->speed = newSpeed;
}

float Ball::getSpeed() const
{
    return speed;
}

// Check if the ball collides with a rectangle and return the side of collision if it does.
std::optional<Side> Ball::getCollisionSide(const Rectangle &rectangle) const
{
    if (!CheckCollisionCircleRec(position, radius, rectangle)) {
        return std::nullopt;
    }

    return getClosestSideToCollision(rectangle);
}

// Get the closest side of the rectangle to the ball's position.
Side Ball::getClosestSideToCollision(const Rectangle &rectangle) const
{
    float distanceToLeft = position.x - rectangle.x;
    float distanceToRight = (rectangle.x + rectangle.width) - position.x;
    float distanceToTop = position.y - rectangle.y;
    float distanceToBottom = (rectangle.y + rectangle.height) - position.y;

    if (const float minDistance = std::min({distanceToLeft, distanceToRight, distanceToTop, distanceToBottom});
        minDistance == distanceToLeft) {
        return Side::LEFT;
    } else if (minDistance == distanceToRight) {
        return Side::RIGHT;
    } else if (minDistance == distanceToTop) {
        return Side::TOP;
    } else {
        return Side::BOTTOM;
    }
}

void Ball::deflect(const Side side)
{
    switch (side) {
        case Side::RIGHT:
        case Side::LEFT:
            movement.x = -movement.x;
            break;
        case Side::TOP:
        case Side::BOTTOM:
            movement.y = -movement.y;
            break;
    }
}

void Ball::move()
{
    position.x += movement.x * speed;
    position.y += movement.y * speed;
}

void Ball::update()
{
    move();
}

void Ball::draw() const
{
    DrawCircleV(position, radius, color);
}
