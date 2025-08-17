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

    void setPosition(Vector2 position);

    Vector2 getPosition();

    void setDimensions(Vector2 dimensions);

    Vector2 getDimensions();

    void setColor(Color color);

    Color getColor();

    void setScore(Vector2 score);

    Vector2 getScore();

    void iterateScore(Side side);

    Rectangle getScoreboardRectangle() const;

    void draw() const;
};

#endif //RAYLIBPONG_SCOREBOARD_H
