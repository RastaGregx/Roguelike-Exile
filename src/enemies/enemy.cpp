#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : position(pos), speed(spd), color(col), health(hp), width(40.0f),
      attackCooldown(1.0f), lastAttackTime(0.0f), pushbackStrength(50.0f), collisionRadius(20.0f) {
    std::srand(std::time(nullptr)); // Seed for randomness
}

// Factory function to create a level-scaled enemy
Enemy Enemy::CreateEnemy(Vector2 pos, int level) {
    float baseSpeed = 100.0f;       // Base speed
    int baseHealth = 50;           // Base health
    float speedMultiplier = 1.1f;  // Speed increases by 10% per level
    int healthIncrement = 10;      // Health increases by 10 per level

    // Scale stats based on level
    float scaledSpeed = baseSpeed * std::pow(speedMultiplier, level - 1);
    int scaledHealth = baseHealth + (healthIncrement * (level - 1));

    return Enemy(pos, scaledSpeed, RED, scaledHealth);
}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<Enemy>& enemies) {
    // Direction vector towards the player
    Vector2 direction = Vector2Subtract(playerPosition, position);

    // Normalize the direction if not zero-length
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    // Calculate the potential new position of the enemy
    Vector2 potentialPosition = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));

    // Check if the new position collides with any objects (walls)
    bool collidesWithWall = false;
    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionCircleRec(potentialPosition, collisionRadius, obj.rect)) {
            collidesWithWall = true;
            break;
        }
    }

    // Check if the new position collides with any other enemies
    bool collidesWithEnemy = false;
    for (const auto& otherEnemy : enemies) {
        if (&otherEnemy != this && otherEnemy.IsAlive() && Vector2Distance(potentialPosition, otherEnemy.position) < collisionRadius * 2) {
            collidesWithEnemy = true;
            break;
        }
    }

    // If no collision with walls or enemies, move towards the player
    if (!collidesWithWall && !collidesWithEnemy) {
        position = potentialPosition;
    } else {
        // Fallback mechanism
        bool moved = false;
        for (int i = 0; i < 5; ++i) { // Try up to 5 random directions
            float randomAngle = ((std::rand() % 360) * PI) / 180.0f; // Random angle in radians
            Vector2 randomDirection = Vector2Rotate(direction, randomAngle);
            Vector2 randomPosition = Vector2Add(position, Vector2Scale(randomDirection, speed * deltaTime));

            // Check collisions for random direction
            bool randomCollides = false;
            for (const auto& obj : objects) {
                if (obj.IsActive() && CheckCollisionCircleRec(randomPosition, collisionRadius, obj.rect)) {
                    randomCollides = true;
                    break;
                }
            }

            for (const auto& otherEnemy : enemies) {
                if (&otherEnemy != this && otherEnemy.IsAlive() && Vector2Distance(randomPosition, otherEnemy.position) < collisionRadius * 2) {
                    randomCollides = true;
                    break;
                }
            }

            if (!randomCollides) {
                position = randomPosition;
                moved = true;
                break;
            }
        }

        if (!moved) {
            // Log if the enemy remains stuck
            std::cout << "Enemy stuck at position: " << position.x << ", " << position.y << std::endl;
        }
    }

    // Handle attack detection (e.g., collision with player)
    float distance = Vector2Distance(position, player.position);
    float combinedRadius = collisionRadius + (player.width / 2);

    if (distance < combinedRadius) {
        player.TakeDamage(5); // Inflict damage on the player
    }

    // Debug: Log enemy position and state
    std::cout << "Enemy Position: " << position.x << ", " << position.y << " | Collision Radius: " << collisionRadius << "\n";
}

// Handle taking damage
void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// Check if the enemy is alive
bool Enemy::IsAlive() const {
    return health > 0;
}

// Draw the enemy
void Enemy::Draw() const {
    if (IsAlive()) {
        DrawCircleV(position, collisionRadius, color);
    }
}
