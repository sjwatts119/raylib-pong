#ifndef RAYLIBPONG_BALL_H
#define RAYLIBPONG_BALL_H
#include "raylib.h"
#include "side.h"
#include <optional>

class Ball
{
private:
    Vector2 position;
    Color color;
    float radius;
    float speed = 5.0f;
    Vector2 movement = {0, 0};

public:
    explicit Ball(Vector2 position, Color color, float radius);

    void setPosition(Vector2 newPosition);

    [[nodiscard]] Vector2 getPosition() const;

    void setMovement(Vector2 newMovement);

    [[nodiscard]] Vector2 getMovement() const;

    void setColor(Color newColor);

    [[nodiscard]] Color getColor() const;

    void setRadius(float newRadius);

    [[nodiscard]] float getRadius() const;

    void setSpeed(float newSpeed);

    [[nodiscard]] float getSpeed() const;

    [[nodiscard]] std::optional<Side> getCollisionSide(const Rectangle &rectangle) const;

    [[nodiscard]] Side getClosestSideToCollision(const Rectangle &rectangle) const;

    void deflect(Side side);

    void move();

    void update();

    void draw() const;
};

#endif //RAYLIBPONG_BALL_H
