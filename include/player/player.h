#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"  // Include raylib for Vector2

// Define the Player struct
struct Player {
    Vector2 position;
    float speed;
    float width;
    float height;
    int hp;
};

// Function declarations
void InitPlayer(Player &player, float x, float y, float speed, float width, float height, int hp);
void TakeDamage(Player &player, int damage);



#endif // PLAYER_H
