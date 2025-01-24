#include "enemies/enemy.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(Vector2 pos, float spd, Color col, int hp)
    : 
    position(pos), 
    speed(spd), 
    color(col), 
    health(hp), 
    width(40.0f),
    attackCooldown(1.0f), lastAttackTime(0.0f), pushbackStrength(50.0f), collisionRadius(20.0f) {
    std::srand(std::time(nullptr));
}

void Enemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    Vector2 toPlayer = Vector2Subtract(playerPosition, position);
    Vector2 direction = Vector2Normalize(toPlayer);
    Vector2 movement = Vector2Scale(direction, speed * deltaTime);
    
    position.x += movement.x;
    position.y += movement.y;

    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionCircleRec(position, collisionRadius, obj.rect)) {
            position.x -= movement.x;
            position.y -= movement.y;
            break;
        }
    }
}

void Enemy::Draw() const {
    DrawRectangleV(position, { 50, 50 }, color);
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
    }
}

bool Enemy::IsAlive() const {
    return health > 0;
}

Vector2 Enemy::GetPosition() const {
    return position;
}

