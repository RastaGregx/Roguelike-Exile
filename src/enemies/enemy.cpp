#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>

Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : position(pos), speed(spd), color(col), health(hp) {}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player &player) {
    Vector2 direction = Vector2Subtract(playerPosition, position);
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    Vector2 scaledMovement = Vector2Scale(direction, speed * deltaTime);
    position = Vector2Add(position, scaledMovement);

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
