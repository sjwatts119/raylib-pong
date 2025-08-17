#include "scoreboard.h"
#include "raylib.h"
#include "side.h"

Scoreboard::Scoreboard(Vector2 position, Vector2 dimensions, Color color)
    : position(position), dimensions(dimensions), color(color)
{
}

void Scoreboard::setPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Scoreboard::getPosition()
{
    return position;
}

void Scoreboard::setDimensions(Vector2 dimensions)
{
    this->dimensions = dimensions;
}

Vector2 Scoreboard::getDimensions()
{
    return dimensions;
}

void Scoreboard::setColor(Color color)
{
    this->color = color;
}

Color Scoreboard::getColor()
{
    return color;
}

void Scoreboard::setScore(Vector2 score)
{
    this->score = score;
}

Vector2 Scoreboard::getScore()
{
    return score;
}

void Scoreboard::iterateScore(Side side)
{
    switch (side) {
        case Side::RIGHT:
            score.x += 1;
            break;
        default:
            score.y += 1;
            break;
    }
}

Rectangle Scoreboard::getScoreboardRectangle() const
{
    return Rectangle{position.x, position.y, dimensions.x, dimensions.y};
}

void Scoreboard::draw() const
{
    DrawRectangleRec(getScoreboardRectangle(), color);

    constexpr int fontSize = 40;
    constexpr float verticalOffset = static_cast<float>(fontSize) / 2.0f;

    DrawText(TextFormat("%d", (int) score.x), position.x + 20, position.y + (dimensions.y / 2) - verticalOffset,
             fontSize, BLACK);
    DrawText(TextFormat("%d", (int) score.y), position.x + dimensions.x - 60,
             position.y + (dimensions.y / 2) - verticalOffset, fontSize, BLACK);
}
