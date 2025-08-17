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
    int radius;
    int speed = 5;
    Vector2 movement = {0, 0};

public:
    explicit Ball(Vector2 position, Color color, int radius);

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setMovement(Vector2 velocity);

    Vector2 getMovement();

    void setColor(Color color);

    Color getColor();

    void setRadius(int radius);

    int getRadius();

    void setSpeed(int speed);

    int getSpeed();

    std::optional<Side> getCollisionSide(const Rectangle &rectangle);

    Side getClosestSideToCollision(const Rectangle &rectangle);

    void deflect(Side side);

    void move();

    void update();

    void draw();
};

#endif //RAYLIBPONG_BALL_H
