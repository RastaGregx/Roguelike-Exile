#include "enemies/tank.h"
#include "player/player.h"
#include "raymath.h"
#include <iostream>

Tank::Tank(Vector2 pos, float spd, Color col, int hp, float armor)
    : Enemy(pos, spd, col, hp), armor(armor) {
        this->width = { 60.0f};
    }

void Tank::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    // Use base class update logic
    Enemy::Update(playerPosition, deltaTime, objects, player, enemies);

    // Add Tank-specific behavior (if any)


}

void Tank::TakeDamage(int damage) {
    int reducedDamage = static_cast<int>(damage * (1.0f - armor)); // Reduce damage based on armor
    Enemy::TakeDamage(reducedDamage); // Call base class TakeDamage with reduced damage
}
