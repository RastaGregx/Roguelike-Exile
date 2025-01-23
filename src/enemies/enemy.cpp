#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : position(pos), speed(spd), color(col), health(hp), width(40.0f),
      attackCooldown(1.0f), lastAttackTime(0.0f), pushbackStrength(50.0f), collisionRadius(20.0f) {
    std::srand(std::time(nullptr));
}


Enemy Enemy::CreateEnemy(Vector2 pos, int level) {
    float baseSpeed = 100.0f;      // Base speed
    int baseHealth = 50;           // Base health
    float speedMultiplier = 1.1f;  // Speed increases by 10% per level
    int healthIncrement = 10;      // Health increases by 10 per level

    float scaledSpeed = baseSpeed * std::pow(speedMultiplier, level - 1);
    int scaledHealth = baseHealth + (healthIncrement * (level - 1));

    return Enemy(pos, scaledSpeed, RED, scaledHealth);
}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<Enemy>& enemies) {
    Vector2 direction = Vector2Subtract(playerPosition, position);
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    Vector2 potentialPosition = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));

    bool collisionDetected = false;

    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionCircleRec(potentialPosition, collisionRadius, obj.rect)) {
            collisionDetected = true;
            break;
        }
    }

    if (!collisionDetected) {
        for (const auto& otherEnemy : enemies) {
            if (&otherEnemy != this && otherEnemy.IsAlive() && Vector2Distance(potentialPosition, otherEnemy.position) < collisionRadius * 2) {
                collisionDetected = true;
                break;
            }
        }
    }

    if (!collisionDetected) {
        position = potentialPosition;
    } else {
        for (auto& otherEnemy : enemies) {
            if (&otherEnemy != this && otherEnemy.IsAlive() && Vector2Distance(position, otherEnemy.position) < collisionRadius * 2) {
                Vector2 pushBackDirection = Vector2Normalize(Vector2Subtract(position, otherEnemy.position));
                if (Vector2Length(pushBackDirection) > 0) {
                    position = Vector2Add(position, Vector2Scale(pushBackDirection, 1.0f));
                }
            }
        }
    }

    float distance = Vector2Distance(position, player.position);
    float combinedRadius = collisionRadius + (player.width / 2);

    attackCooldown -= deltaTime;

    if (distance < combinedRadius) {
        if (attackCooldown <= 0) {
            player.TakeDamage(5);
            Vector2 pushBackDirection = Vector2Normalize(Vector2Subtract(player.position, position));
            position = Vector2Add(position, Vector2Scale(pushBackDirection, -pushbackStrength)); // Push the enemy back
            attackCooldown = 1.0f;
        }
    }
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Enemy::IsAlive() const {
    return health > 0;
}

void Enemy::Draw() const {
    if (IsAlive()) {
        DrawCircleV(position, collisionRadius, color);
    }
}