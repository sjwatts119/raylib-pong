#include "ball.h"
#include "side.h"

Ball::Ball(Vector2 position, Color color, int radius)
    : position(position), color(color), radius(radius)
{
    // Set a random initial movement direction
    movement.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
    movement.y = GetRandomValue(0, 1) == 0 ? -1 : 1;
}

void Ball::setPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Ball::getPosition()
{
    return position;
}

void Ball::setMovement(Vector2 movement)
{
    this->movement = movement;
}

Vector2 Ball::getMovement()
{
    return movement;
}

void Ball::setColor(Color color)
{
    this->color = color;
}

Color Ball::getColor()
{
    return color;
}

void Ball::setRadius(int radius)
{
    this->radius = radius;
}

int Ball::getRadius()
{
    return radius;
}

void Ball::setSpeed(int speed)
{
    this->speed = speed;
}

int Ball::getSpeed()
{
    return speed;
}

// Check if the ball collides with a rectangle and return the side of collision if it does.
std::optional<Side> Ball::getCollisionSide(const Rectangle &rectangle)
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

    float minDistance = std::min({distanceToLeft, distanceToRight, distanceToTop, distanceToBottom});

    if (minDistance == distanceToLeft) {
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
            movement.x = -movement.x;
            break;
        case Side::LEFT:
            movement.x = -movement.x;
            break;
        case Side::TOP:
            movement.y = -movement.y;
            break;
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

void Ball::draw()
{
    DrawCircleV(position, radius, color);
}
