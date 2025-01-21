#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Define the Player struct
struct Player {
    Vector2 position;
    float speed;
    float width;
    float height;
    int hp;

    // Add member function
    void TakeDamage(int damage);
};

// Function declaration for initialization
void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp);
void DrawPlayer(const Player &player);

#endif // PLAYER_H
