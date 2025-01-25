#include "enemies/tank.h"

Tank::Tank(Vector2 pos, float spd, Color col, int hp, float armor, const std::string& texturePath)
    : Enemy(pos, spd, col, hp, 0.0f, 0.0f), armor(armor) {
    // Load the texture from the given path
    texture = LoadTexture(texturePath.c_str());

    // Set sprite-based dimensions for collision
    if (hasTexture()) {
        width = static_cast<float>(texture.width);
        height = static_cast<float>(texture.height);
        collisionRadius = (width + height) / 4.0f; // Update collision radius based on texture size
    }
}

Tank::~Tank() {
    // Unload the texture to prevent memory leaks
    UnloadTexture(texture);
}

void Tank::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies) {
    // Call base class update logic
    Enemy::Update(playerPosition, deltaTime, objects, player, enemies);

    // Additional Tank-specific logic (if needed)
}

void Tank::TakeDamage(int damage) {
    // Apply armor reduction to the damage
    int finalDamage = static_cast<int>(damage * (1 - armor));
    Enemy::TakeDamage(finalDamage);
}

bool Tank::hasTexture() const {
    // Ensure the texture is valid by checking its dimensions
    return texture.width > 0 && texture.height > 0;
}

Texture2D Tank::getTexture() const {
    return texture;
}