// src/player/movement.cpp
#include "player/movement.h"

const float playerSpeed = 200.0f;  // Speed in pixels per second

void UpdatePlayerMovement(Vector2 &playerPosition, float deltaTime) {
    // Player movement (WASD keys) using deltaTime
    if (IsKeyDown(KEY_W)) playerPosition.y -= playerSpeed * deltaTime;
    if (IsKeyDown(KEY_S)) playerPosition.y += playerSpeed * deltaTime;
    if (IsKeyDown(KEY_A)) playerPosition.x -= playerSpeed * deltaTime;
    if (IsKeyDown(KEY_D)) playerPosition.x += playerSpeed * deltaTime;

    // Keep the player within the screen boundaries
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if (playerPosition.x < 0) playerPosition.x = 0;
    if (playerPosition.x + 50 > screenWidth) playerPosition.x = screenWidth - 50;
    if (playerPosition.y < 0) playerPosition.y = 0;
    if (playerPosition.y + 50 > screenHeight) playerPosition.y = screenHeight - 50;
}
