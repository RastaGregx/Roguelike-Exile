#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player {
    Vector2 position;
    float speed;
    float width;
    float height;
    int hp;
    Texture2D texture;

    void TakeDamage(int damage);
};

void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp, const char* spritePath);
void DrawPlayer(const Player &player);

#endif
