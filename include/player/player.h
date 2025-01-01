// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Vector2 position;  // The position of the player on the screen
    float speed;       // The movement speed of the player

    Player(float x, float y, float spd);

};

#endif // PLAYER_H
