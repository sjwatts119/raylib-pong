#ifndef RAYLIBPONG_BARRIER_H
#define RAYLIBPONG_BARRIER_H

#include "raylib.h"

class Barrier
{
private:
    Vector2 dimensions;
    Vector2 position;
    Color color = WHITE;

public:
    explicit Barrier(Vector2 dimensions, Vector2 position, Color color = SKYBLUE);

    void setDimensions(Vector2 dimensions);

    Vector2 getDimensions();

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setColor(Color color);

    Color getColor();

    Rectangle getRectangle();

    void draw();
};


#endif //RAYLIBPONG_BARRIER_H