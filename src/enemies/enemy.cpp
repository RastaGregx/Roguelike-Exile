#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>

Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : position(pos), speed(spd), color(col), health(hp) {}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player) {
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
        if (obj.IsActive() && CheckCollisionCircleRec(potentialPosition, 20.0f, obj.rect)) {
            collidesWithWall = true;
            break;
        }
    }

    // If no collision, move towards the player
    if (!collidesWithWall) {
        position = potentialPosition;
    } else {
        // If there’s a collision, try moving in other directions
        // For example, move to the right
        Vector2 rightDirection = Vector2Rotate(direction, PI / 2); // Rotate 90 degrees
        Vector2 potentialRight = Vector2Add(position, Vector2Scale(rightDirection, speed * deltaTime));

        // Check if the right movement is clear
        bool canMoveRight = true;
        for (const auto& obj : objects) {
            if (obj.IsActive() && CheckCollisionCircleRec(potentialRight, 20.0f, obj.rect)) {
                canMoveRight = false;
                break;
            }
        }

        // If we can move right, go right
        if (canMoveRight) {
            position = potentialRight;
        } else {
            // Otherwise, try moving left
            Vector2 leftDirection = Vector2Rotate(direction, -PI / 2); // Rotate -90 degrees
            Vector2 potentialLeft = Vector2Add(position, Vector2Scale(leftDirection, speed * deltaTime));

            // Check if the left movement is clear
            bool canMoveLeft = true;
            for (const auto& obj : objects) {
                if (obj.IsActive() && CheckCollisionCircleRec(potentialLeft, 20.0f, obj.rect)) {
                    canMoveLeft = false;
                    break;
                }
            }

            // Move left if possible
            if (canMoveLeft) {
                position = potentialLeft;
            }
        }
    }

    // Continue to handle the player's attack and other behaviors like before
    float distance = Vector2Distance(position, player.position);
    float combinedRadius = (width / 2) + (player.width / 2);

    std::cout << "Enemy Pos: " << position.x << ", " << position.y
              << " | Player Pos: " << player.position.x << ", " << player.position.y
              << " | Distance: " << distance << " | Combined Radius: " << combinedRadius << "\n";

    if (distance < combinedRadius) {
        ::TakeDamage(player, 10);
        std::cout << "Collision detected! Player HP: " << player.hp << "\n";
    }
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
