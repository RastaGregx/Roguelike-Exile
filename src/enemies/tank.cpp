#include "enemies/tank.h"

Tank::Tank(Vector2 pos, float spd, Color col, int hp, float armor, const std::string& texturePath)
    : Enemy(pos, spd, col, hp), armor(armor) {
    // Load the texture from the given path
    texture = LoadTexture(texturePath.c_str());
}

void Tank::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    // Tank-specific update logic goes here
}

void Tank::TakeDamage(int damage) {
    // Apply armor reduction to the damage
    int finalDamage = static_cast<int>(damage * (1 - armor));
    Enemy::TakeDamage(finalDamage); // Call base class method to apply damage
}

bool Tank::hasTexture() const {
    return texture.width > 0 && texture.height > 0;
}

Texture2D Tank::getTexture() const {
    return texture;
}
