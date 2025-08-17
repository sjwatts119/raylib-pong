#ifndef RAYLIBPONG_PADDLE_H
#define RAYLIBPONG_PADDLE_H
#include "barrier.h"

class Paddle : public Barrier
{
protected:
    Rectangle playArea;

public:
    Paddle(Vector2 dimensions, Vector2 position, Rectangle playArea, Color color = RED);

    void draw() override;

    void update();

    void applyMovement();

    // Add paddle-specific methods
    void moveUp();

    void moveDown();
};

#endif //RAYLIBPONG_PADDLE_H