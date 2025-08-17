#ifndef RAYLIBPONG_SCOREBOARD_H
#define RAYLIBPONG_SCOREBOARD_H
#include "raylib.h"
#include "side.h"

class Scoreboard
{
private:
    Vector2 position;
    Vector2 dimensions;
    Color color;
    Vector2 score = {0, 0};

public:
    Scoreboard(Vector2 position, Vector2 dimensions, Color color = WHITE);

    void setPosition(Vector2 newPosition);

    [[nodiscard]] Vector2 getPosition() const;

    void setDimensions(Vector2 newDimensions);

    [[nodiscard]] Vector2 getDimensions() const;

    void setColor(Color newColor);

    [[nodiscard]] Color getColor() const;

    void setScore(Vector2 newScore);

    [[nodiscard]] Vector2 getScore() const;

    void iterateScore(Side side);

    [[nodiscard]] Rectangle getScoreboardRectangle() const;

    void draw() const;
};

#endif //RAYLIBPONG_SCOREBOARD_H
