// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player/player.h"  // Include player header for position
#include "raymath.h"  // For vector math functions like Vector2Subtract


// enemy.h

class Enemy {
public:
    Vector2 position;
    float speed;
    Color color;

    // Constructor to initialize position, speed, and color
    Enemy(Vector2 pos, float spd, Color col)
        : position(pos), speed(spd), color(col) {}

    // Update the enemy's behavior (follow player)
    void Update(Vector2 playerPosition, float deltaTime) {
        // Calculate direction vector from enemy to player
        Vector2 direction = playerPosition - position;  // Subtract directly

        // Normalize the direction for consistent speed
        if (Vector2Length(direction) > 0) {
            direction = Vector2Normalize(direction);  // Normalize to get a unit vector
        }

        // Update the enemy's position
        position = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));
    }

    // Draw the enemy on the screen
    void Draw() const {
        DrawCircleV(position, 20, color);  // Draw the enemy as a circle
    }
};


#endif // ENEMY_H
