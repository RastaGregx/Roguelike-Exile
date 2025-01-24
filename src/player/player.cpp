#include "player/player.h"
#include "raylib.h"

void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp, const char* spritePath) {
    player.position = { x, y };
    player.speed = speed;
    player.width = width;
    player.height = height;
    player.hp = hp;
    player.texture = LoadTexture(spritePath); 
    player.collisionRadius = width / 2;  // Assuming the collision radius is based on the player's width
}

void Player::TakeDamage(int damage) {
    hp -= damage;  // Subtract damage instead of adding
    if (hp < 0) hp = 0;  // Prevent health from going negative
}

Vector2 Player::GetPosition() const {
    return position;
}

float Player::GetCollisionRadius() const {
    return collisionRadius;
}

void DrawPlayer(const Player &player) {
    DrawTextureEx(player.texture, { player.position.x - player.width / 2, player.position.y - player.height / 2 }, 0.0f, 1.0f, WHITE);
}

void UnloadPlayer(Player &player) {
    UnloadTexture(player.texture); // Free the texture from memory
}
