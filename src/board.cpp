#include "board.h"
#include <vector>
#include "barrier.h"
#include "ball.h"
#include "paddle.h"
#include "raylib.h"
#include "side.h"

Board::Board(const Vector2 dimensions, const Vector2 position, const Color color)
    : dimensions(dimensions),
      position(position),
      color(color),
      scoreboard(createInitialScoreboard()),
      ball(createInitialBall())
{
    initColliders();
}

void Board::setDimensions(const Vector2 newDimensions)
{
    this->dimensions = newDimensions;
}

Vector2 Board::getDimensions() const
{
    return dimensions;
}

void Board::setPosition(const Vector2 newPosition)
{
    this->position = newPosition;
}

Vector2 Board::getPosition() const
{
    return position;
}

void Board::setColor(const Color newColor)
{
    this->color = newColor;
}

Color Board::getColor() const
{
    return color;
}

Rectangle Board::getGameRectangle() const
{
    return Rectangle{position.x, position.y, dimensions.x, dimensions.y - 100};
}

Rectangle Board::getPlayAreaRectangle() const
{
    auto [x, y, width, height] = getGameRectangle();
    return Rectangle{
        x,
        y + barrierWidth,
        width,
        height - (2 * barrierWidth)
    };
}

std::vector<std::unique_ptr<Barrier>> Board::getColliders() const
{
    std::vector<std::unique_ptr<Barrier>> colliders;

    for (const auto &barrier: barriers) {
        colliders.push_back(std::make_unique<Barrier>(barrier));
    }

    for (const auto &paddle: paddles) {
        colliders.push_back(std::make_unique<Barrier>(paddle));
    }

    return colliders;
}

bool Board::hasWinningSide() const
{
    return getWinningSide().has_value();
}

std::optional<Side> Board::getWinningSide() const
{
    if (CheckCollisionCircleRec(ball.getPosition(), ball.getRadius(), getPlayAreaRectangle())) {
        return std::nullopt;
    }

    return ball.getPosition().x < position.x ? Side::LEFT : Side::RIGHT;
}

void Board::applyPaddleMovements()
{
    for (auto &paddle: paddles) {
        paddle.applyMovement(ball);
    }
}

void Board::applyBallDeflections()
{
    for (const auto &collider: getColliders()) {
        std::optional<Side> collisionSide = ball.getCollisionSide(collider->getRectangle());

        if (!collisionSide.has_value()) {
            continue;
        }

        ball.deflect(collisionSide.value());

        pushBallOutOfCollision(collider->getRectangle(), collisionSide.value());
    }
}

void Board::pushBallOutOfCollision(const Rectangle& rect, const Side collisionSide)
{
    Vector2 ballPos = ball.getPosition();
    const float radius = ball.getRadius();
    constexpr float buffer = 1.0f;

    switch (collisionSide) {
        case Side::LEFT:
            ballPos.x = rect.x - radius - buffer;
            break;
        case Side::RIGHT:
            ballPos.x = rect.x + rect.width + radius + buffer;
            break;
        case Side::TOP:
            ballPos.y = rect.y - radius - buffer;
            break;
        case Side::BOTTOM:
            ballPos.y = rect.y + rect.height + radius + buffer;
            break;
    }

    ball.setPosition(ballPos);
}

void Board::initColliders()
{
    barriers.clear();
    paddles.clear();

    auto [x, y, width, height] = getGameRectangle();

    // Add top and bottom barriers
    barriers.emplace_back(
        Vector2{width, barrierWidth},
        Vector2{x, y}
    );
    barriers.emplace_back(
        Vector2{width, barrierWidth},
        Vector2{x, y + height - barrierWidth}
    );

    // Add left and right paddles
    paddles.emplace_back(
        Vector2{barrierWidth, paddleHeight},
        Vector2{x + paddleInset, y + (height / 2) - (paddleHeight / 2)},
        getPlayAreaRectangle(),
        ControlMode::ARROW_KEYS
    );
    paddles.emplace_back(
        Vector2{barrierWidth, paddleHeight},
        Vector2{
            x + width - paddleInset - barrierWidth,
            y + (height / 2) - (paddleHeight / 2)
        },
        getPlayAreaRectangle(),
        ControlMode::COMPUTER
    );
}

Ball Board::createInitialBall() const
{
    auto [x, y, width, height] = getGameRectangle();
    const Vector2 playAreaCenter = {
        x + (width / 2),
        y + (height / 2)
    };

    return Ball(playAreaCenter, WHITE, 10.0f);
}

Scoreboard Board::createInitialScoreboard() const
{
    const Rectangle gameRect = getGameRectangle();

    return Scoreboard(
        Vector2{position.x, gameRect.y + gameRect.height},
        Vector2{dimensions.x, std::abs(gameRect.height - dimensions.y)}
    );
}

void Board::reset()
{
    ball = createInitialBall();
}

void Board::update()
{
    applyPaddleMovements();

    ball.update();

    applyBallDeflections();

    if (const std::optional<Side> winningSide = getWinningSide()) {
        scoreboard.iterateScore(winningSide.value());
        reset();
    }
}

void Board::draw() const
{
    DrawRectangleRec(getGameRectangle(), getColor());

    for (const auto &collider: getColliders()) {
        collider->draw();
    }

    ball.draw();

    scoreboard.draw();
}
