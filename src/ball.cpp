#include "ball.h"
#include "side.h"

Ball::Ball(Vector2 position, Color color, int radius)
    : position(position), color(color), radius(radius)
{
    movement.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
    movement.y = GetRandomValue(1, 1) == 0 ? -1 : 1;
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

void Ball::deflect(Side side)
{
    switch (side) {
        case Side::Right:
            movement.x = -movement.x;
            break;
        case Side::Left:
            movement.x = -movement.x;
            break;
        case Side::Top:
            movement.y = -movement.y;
            break;
        case Side::Bottom:
            movement.y = -movement.y;
            break;
    }
}

void Ball::move()
{
    position.x += movement.x;
    position.y += movement.y;
}

void Ball::update()
{
    move();
}

void Ball::draw()
{
    DrawCircleV(position, radius, color);
}
