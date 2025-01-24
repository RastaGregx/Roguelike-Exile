#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cfloat>


Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : 
    position(pos), 
    speed(spd), 
    color(col), 
    health(hp), 
    width(40.0f),
    attackCooldown(1.0f), 
    lastAttackTime(0.0f), 
    pushbackStrength(50.0f), 
    collisionRadius(20.0f),
    active(true) {  // Added active flag initialization
    std::srand(std::time(nullptr));
}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    Vector2 toPlayer = Vector2Subtract(playerPosition, position);
    Vector2 direction = Vector2Normalize(toPlayer);
    Vector2 movement = Vector2Scale(direction, speed * deltaTime);

    // Save the original position for collision detection
    Vector2 originalPosition = position;

    // Attempt to move toward the player
    position.x += movement.x;
    position.y += movement.y;

    bool collided = false;

    // Check collision with objects
    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionCircleRec(position, collisionRadius, obj.rect)) {
            // Revert position on collision
            position = originalPosition;
            collided = true;
            break;
        }
    }

    // If the enemy collides, try to find a better path
    if (collided) {
        const float minDistance = 10.0f; // Minimum distance from the wall
        for (const auto& obj : objects) {
            if (obj.IsActive() && CheckCollisionCircleRec(position, collisionRadius, obj.rect)) {
                Vector2 wallDirection = { 0.0f, 0.0f };

                if (position.x < obj.rect.x) {
                    wallDirection.x = -1.0f;
                } else if (position.x > obj.rect.x + obj.rect.width) {
                    wallDirection.x = 1.0f;
                }

                if (position.y < obj.rect.y) {
                    wallDirection.y = -1.0f;
                } else if (position.y > obj.rect.y + obj.rect.height) {
                    wallDirection.y = 1.0f;
                }

                position = Vector2Add(position, Vector2Scale(Vector2Normalize(wallDirection), minDistance));
            }
        }
    }

    // Handle collision with player
    if (CheckCollisionCircles(position, collisionRadius, player.position, player.GetCollisionRadius())) {
        if (attackCooldown <= 0.0f) {
            player.TakeDamage(10); // Deal damage to the player
            attackCooldown = 1.0f; // Reset attack cooldown
        }
    }

    // Update attack cooldown
    if (attackCooldown > 0.0f) {
        attackCooldown -= deltaTime;
    }
}



void Enemy::Draw() const {
    DrawRectangleV(position, { 50, 50 }, color);
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        active = false;  // Add this line
    }
}

bool Enemy::IsAlive() const {
    return active;  // Change this to check the new active flag
}

Vector2 Enemy::GetPosition() const {
    return position;
}

