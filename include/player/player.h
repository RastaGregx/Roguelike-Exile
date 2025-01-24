#pragma once

#include "raylib.h"

class Player {
public:
    // Player properties
    Vector2 position;      // Position of the player
    float speed;           // Movement speed
    float width;           // Width of the player (sprite-based dimension)
    float height;          // Height of the player (sprite-based dimension)
    int hp;                // Health points
    Texture2D texture;     // Sprite texture
    float collisionRadius; // Collision radius (for circle-based collision)

    // Method to reduce health when taking damage
    void TakeDamage(int damage);

    // Get the player's position
    Vector2 GetPosition() const;

    // Get the collision radius for compatibility with other collision systems
    float GetCollisionRadius() const;
};

// Function prototypes
void InitPlayer(Player& player, float x, float y, float speed, float width, float height, int hp, const char* spritePath);
void DrawPlayer(const Player& player);
void UnloadPlayer(Player& player);
