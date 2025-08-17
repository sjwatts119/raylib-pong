#include "paddle.h"

Paddle::Paddle(const Vector2 dimensions, const Vector2 position, const Rectangle playArea, const ControlMode controlMode, const Color color)
    : Barrier(dimensions, position, color),
      playArea(playArea),
      controlMode(controlMode)
{
}

ControlMode Paddle::getControlMode() const
{
    return controlMode;
}

void Paddle::setControlMode(const ControlMode newControlMode)
{
    this->controlMode = newControlMode;
}

void Paddle::moveUp()
{
    if (position.y - speed < playArea.y) {
        return;
    }

    position.y -= speed;
}

void Paddle::moveDown()
{
    if (position.y + dimensions.y + speed > playArea.y + playArea.height) {
        return;
    }

    position.y += speed;
}

std::optional<Direction> Paddle::getMovementIntent(const Ball &ball) const
{
    switch (controlMode) {
        case (ControlMode::ARROW_KEYS):
            if (IsKeyDown(KEY_UP)) {
                return Direction::UP;
            }

            if (IsKeyDown(KEY_DOWN)) {
                return Direction::DOWN;
            }

            break;
        case (ControlMode::COMPUTER):
            if (ball.getPosition().y < position.y) {
                return Direction::UP;
            }

            if (ball.getPosition().y > position.y + dimensions.y) {
                return Direction::DOWN;
            }

            break;
    }

    return std::nullopt;
}

void Paddle::applyMovement(const Ball &ball)
{
    const std::optional<Direction> movementIntent = getMovementIntent(ball);

    if (!movementIntent.has_value()) {
        return;
    }

    switch (movementIntent.value()) {
        case(Direction::UP):
            moveUp();
            break;
        case(Direction::DOWN):
            moveDown();
            break;
        default:
            break;
    }
}

void Paddle::draw()
{
    DrawRectangleRec(getRectangle(), RED);
}
