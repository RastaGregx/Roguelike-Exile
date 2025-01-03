#include "player/player.h"
#include "raylib.h"

void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp) {
    player.position = { x, y };
    player.speed = speed;
    player.width = width;
    player.height = height;
    player.hp = hp; // Initialize health
}

// Reduce HP when player is hit
void TakeDamage(Player &player, int damage) {
    player.hp -= damage;
    if (player.hp < 0) player.hp = 0;  // Prevent negative HP
}

void DrawPlayer(const Player &player) {
    DrawCircleV(player.position, player.width / 2, BLUE);  // Drawing player as a circle
}