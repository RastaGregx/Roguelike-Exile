#include "player/player.h"
#include "raylib.h"

void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp) {
    player.position = { x, y };
    player.speed = speed;
    player.width = width;
    player.height = height;
    player.hp = hp;
}

void Player::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void DrawPlayer(const Player &player) {
    DrawCircleV(player.position, player.width / 2, BLUE);
}
