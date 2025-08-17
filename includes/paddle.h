#ifndef RAYLIBPONG_PADDLE_H
#define RAYLIBPONG_PADDLE_H
#include <optional>

#include "ball.h"
#include "barrier.h"
#include "controlMode.h"
#include "direction.h"

class Paddle final : public Barrier
{
protected:
    float speed = 10.0f;
    Rectangle playArea;
    ControlMode controlMode;

public:
    Paddle(Vector2 dimensions, Vector2 position, Rectangle playArea, ControlMode controlMode, Color color = RED);

    [[nodiscard]] ControlMode getControlMode() const;

    void setControlMode(ControlMode newControlMode);

    [[nodiscard]] std::optional<Direction> getMovementIntent(const Ball &ball) const;

    void applyMovement(Direction direction);

    void moveUp();

    void moveDown();

    void draw() override;
};

#endif //RAYLIBPONG_PADDLE_H
