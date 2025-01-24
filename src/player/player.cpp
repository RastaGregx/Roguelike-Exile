#include "player/player.h"
#include "raylib.h"

void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp, const char* spritePath) {
    player.position = { x, y };
    player.speed = speed;
    player.width = width;
    player.height = height;
    player.hp = hp;
    player.texture = LoadTexture(spritePath); 
}

void Player::TakeDamage(int damage) {
    hp += damage;
    if (hp < 0) hp = 0;
}

void DrawPlayer(const Player &player) {
    DrawTextureEx(player.texture, { player.position.x - player.width / 2, player.position.y - player.height / 2 }, 0.0f, 1.0f, WHITE);
}

void UnloadPlayer(Player &player) {
    UnloadTexture(player.texture); // Free the texture from memory
}