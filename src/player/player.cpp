// src/player/player.cpp
#include "player/player.h"
#include "raylib.h"

void InitPlayer(Player &player, char name, float x, float y, float speed) {
    player.position = { x, y };
    player.speed = speed;
}

