#ifndef RAYLIBPONG_BARRIER_H
#define RAYLIBPONG_BARRIER_H

#include "raylib.h"

class Barrier
{
protected:
    Vector2 dimensions;
    Vector2 position;
    Color color = WHITE;

public:
    explicit Barrier(Vector2 dimensions, Vector2 position, Color color = SKYBLUE);

    virtual ~Barrier() = default;

    void setDimensions(Vector2 newDimensions);

    [[nodiscard]] Vector2 getDimensions() const;

    void setPosition(Vector2 newPosition);

    [[nodiscard]] Vector2 getPosition() const;

    void setColor(Color newColor);

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] Rectangle getRectangle() const;

    virtual void draw();
};

#endif //RAYLIBPONG_BARRIER_H
