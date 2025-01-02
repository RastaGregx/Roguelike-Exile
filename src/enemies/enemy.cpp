#include "enemies/enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : position(pos), speed(spd), color(col), health(hp) {}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects) {
    // Same Update logic as before, with movement and collision checks
    Vector2 direction = Vector2Subtract(playerPosition, position);

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    Vector2 proposedPosition = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));
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

    position = adjustedPosition;
}

void Enemy::TakeDamage(int damage) {
    health -= damage; // Reduce health by the damage amount
    if (health < 0) health = 0; // Prevent health from going negative
}


bool Enemy::IsAlive() const {
    return health > 0; // Enemy is alive if health is greater than 0
}

void Enemy::Draw() const {
    if (IsAlive()) {
        DrawCircleV(position, 20, color);
    }
}
