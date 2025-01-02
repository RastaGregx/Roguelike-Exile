#include "enemies/enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, float spd, Color col)
    : position(pos), speed(spd), color(col) {}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects) {
    // Calculate direction towards the player
    Vector2 direction = Vector2Subtract(playerPosition, position);

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    // Proposed new position
    Vector2 proposedPosition = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));

    // Handle collisions by resolving movement separately for X and Y axes
    Vector2 adjustedPosition = position;

    // Resolve X movement
    Vector2 proposedXPosition = { proposedPosition.x, position.y };
    bool collidingX = false;
    for (const auto& obj : objects) {
        if (CheckCollisionCircleRec(proposedXPosition, 20.0f, obj.rect)) {
            collidingX = true;
            break;
        }
    }
    if (!collidingX) {
        adjustedPosition.x = proposedXPosition.x;
    }

    // Resolve Y movement
    Vector2 proposedYPosition = { position.x, proposedPosition.y };
    bool collidingY = false;
    for (const auto& obj : objects) {
        if (CheckCollisionCircleRec(proposedYPosition, 20.0f, obj.rect)) {
            collidingY = true;
            break;
        }
    }
    if (!collidingY) {
        adjustedPosition.y = proposedYPosition.y;
    }

    // Update position to the adjusted position
    position = adjustedPosition;
}


void Enemy::Draw() const {
    DrawCircleV(position, 20, color); // Draw enemy as a circle
}
