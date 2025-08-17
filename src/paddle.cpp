#include "paddle.h"

Paddle::Paddle(const Vector2 dimensions, const Vector2 position, const Rectangle playArea, const Color color)
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
        moveUp();
    }

    if (IsKeyDown(KEY_DOWN)) {
        moveDown();
    }
}

void Paddle::update()
{
    applyMovement();
}

void Paddle::draw()
{
    update();

    DrawRectangleRec(getRectangle(), RED);
}
