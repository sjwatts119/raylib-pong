#include "paddle.h"

Paddle::Paddle(Vector2 dimensions, Vector2 position, Rectangle playArea, Color color)
    : Barrier(dimensions, position, color),
    playArea(playArea)
{
}

void Paddle::moveUp()
{
    if (position.y - 5 < playArea.y) {
        return;
    }

    position.y -= 5;
}

void Paddle::moveDown()
{
    if (position.y + dimensions.y + 5 > playArea.y + playArea.height) {
        return;
    }

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