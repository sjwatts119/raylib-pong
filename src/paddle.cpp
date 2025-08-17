#include "paddle.h"

Paddle::Paddle(Vector2 dimensions, Vector2 position, Color color)
    : Barrier(dimensions, position, color)
{
}

void Paddle::moveUp()
{
    position.y -= 5;
}

void Paddle::moveDown()
{
    position.y += 5;
}

void Paddle::applyMovement()
{
    if (IsKeyDown(KEY_UP)) {
        Paddle::moveUp();
    }

    if (IsKeyDown(KEY_DOWN)) {
        Paddle::moveDown();
    }
}

void Paddle::update()
{
    applyMovement();
}

void Paddle::draw()
{
    Paddle::update();

    DrawRectangleRec(getRectangle(), RED);
}