#include "scoreboard.h"
#include "raylib.h"
#include "side.h"

Scoreboard::Scoreboard(const Vector2 position, const Vector2 dimensions, const Color color)
    : position(position), dimensions(dimensions), color(color)
{
}

void Scoreboard::setPosition(const Vector2 newPosition)
{
    this->position = newPosition;
}

Vector2 Scoreboard::getPosition() const
{
    return position;
}

void Scoreboard::setDimensions(const Vector2 newDimensions)
{
    this->dimensions = newDimensions;
}

Vector2 Scoreboard::getDimensions() const
{
    return dimensions;
}

void Scoreboard::setColor(const Color newColor)
{
    this->color = newColor;
}

Color Scoreboard::getColor() const
{
    return color;
}

void Scoreboard::setScore(const Vector2 newScore)
{
    this->score = newScore;
}

Vector2 Scoreboard::getScore() const
{
    return score;
}

void Scoreboard::iterateScore(const Side side)
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
    constexpr float horizontalInset = 40.0f;

    DrawText(TextFormat("%d", static_cast<int>(score.x)),
             static_cast<int>(position.x + horizontalInset),
             static_cast<int>(position.y + (dimensions.y / 2) - verticalOffset),
             fontSize, BLACK);
    DrawText(TextFormat("%d", static_cast<int>(score.y)),
             static_cast<int>(position.x + dimensions.x - horizontalInset - static_cast<float>(MeasureText(TextFormat("%d", static_cast<int>(score.y)), fontSize))),
             static_cast<int>(position.y + (dimensions.y / 2) - verticalOffset),
             fontSize, BLACK);
}