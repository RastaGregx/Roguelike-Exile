#include "enemies/enemy.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy(Vector2 pos, float spd, Color col, int hp, float w, float h)
    : position(pos), speed(spd), color(col), health(hp), 
      width(w), height(h), collisionRadius((w + h) / 4.0f),
      attackCooldown(1.0f), lastAttackTime(0.0f), active(true) {
    std::srand(std::time(nullptr));
}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    Vector2 toPlayer = Vector2Subtract(playerPosition, position);
    Vector2 direction = Vector2Normalize(toPlayer);
    Vector2 movement = Vector2Scale(direction, speed * deltaTime);

    Vector2 proposedPosition = {
        position.x + movement.x,
        position.y + movement.y
    };

    // Separate X and Y axis collision checks
    Vector2 xOnlyPosition = { proposedPosition.x, position.y };
    Vector2 yOnlyPosition = { position.x, proposedPosition.y };

    bool xCollision = false;
    bool yCollision = false;

    // Check X-axis movement
    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionRecs(
            { xOnlyPosition.x, xOnlyPosition.y, width, height }, 
            obj.rect)) {
            xCollision = true;
            break;
        }
    }

    // Check Y-axis movement
    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionRecs(
            { yOnlyPosition.x, yOnlyPosition.y, width, height }, 
            obj.rect)) {
            yCollision = true;
            break;
        }
    }

    // Update position based on collision checks
    if (!xCollision) position.x = xOnlyPosition.x;
    if (!yCollision) position.y = yOnlyPosition.y;

    // Player collision
    if (CheckCollisionRecs(
        { position.x, position.y, width, height }, 
        { player.position.x, player.position.y, player.width, player.height })) {
        if (attackCooldown <= 0.0f) {
            player.TakeDamage(10);
            attackCooldown = 1.0f;
        }
    }

    // Reduce attack cooldown
    if (attackCooldown > 0.0f) {
        attackCooldown -= deltaTime;
    }
}
void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        active = false;
    }
}

void Enemy::Draw() const {
    DrawRectangleV(position, { width, height }, color);
}

bool Enemy::IsAlive() const {
    return active;
}

Vector2 Enemy::GetPosition() const {
    return position;
}

float Enemy::GetCollisionRadius() const {
    return collisionRadius;
}
