#include "player/player.h"
#include "raylib.h"

// Initialize player properties
void InitPlayer(Player& player, float x, float y, float speed, float width, float height, int hp, const char* spritePath) {
    player.position = { x, y };
    player.speed = speed;
    player.width = width;
    player.height = height;
    player.hp = hp;
    player.texture = LoadTexture(spritePath); 
    player.collisionRadius = width / 2;  // Assuming the collision radius is based on the player's width
}

// Reduce player's health when taking damage
void Player::TakeDamage(int damage) {
    hp -= damage;  // Subtract damage
    if (hp < 0) hp = 0;  // Prevent health from going negative
}

// Get player's position
Vector2 Player::GetPosition() const {
    return position;
}

// Get collision radius for the player
float Player::GetCollisionRadius() const {
    return collisionRadius;
}

// Draw the player using their texture
void DrawPlayer(const Player& player) {
    DrawTextureEx(player.texture, { player.position.x - player.width / 2, player.position.y - player.height / 2 }, 0.0f, 1.0f, WHITE);
}

// Free texture memory when the player is unloaded
void UnloadPlayer(Player& player) {
    UnloadTexture(player.texture);
}
