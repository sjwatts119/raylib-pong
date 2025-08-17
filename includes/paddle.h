#ifndef RAYLIBPONG_PADDLE_H
#define RAYLIBPONG_PADDLE_H
#include "barrier.h"

class Paddle : public Barrier
{
public:
    // Constructor that forwards to parent
    Paddle(Vector2 dimensions, Vector2 position, Color color = RED);

    void draw() override;

    void update();

    void applyMovement();

    // Add paddle-specific methods
    void moveUp();
    void moveDown();
};

#endif //RAYLIBPONG_PADDLE_H