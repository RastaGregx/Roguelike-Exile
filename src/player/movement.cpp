#include "player/movement.h"
#include "raylib.h"
#include "object.h"
#include <vector>

const float playerSpeed = 300.0f;  // Speed in pixels per second

void UpdatePlayerMovement(Vector2 &playerPosition, float deltaTime, const std::vector<Object>& objects, Camera2D camera) {
    const float playerWidth = 45.0f;
    const float playerHeight = 45.0f;

    // Original rectangle before movement
    Rectangle originalPlayerRect = {playerPosition.x, playerPosition.y, playerWidth, playerHeight};

    // Process movement
    Vector2 proposedPosition = playerPosition;

    if (IsKeyDown(KEY_W)) proposedPosition.y -= playerSpeed * deltaTime;
    // Camera target follows player
        camera.target = (Vector2){ playerPosition.x + 20, playerPosition.y + 20 };
    if (IsKeyDown(KEY_S)) proposedPosition.y += playerSpeed * deltaTime;
    if (IsKeyDown(KEY_A)) proposedPosition.x -= playerSpeed * deltaTime;
    if (IsKeyDown(KEY_D)) proposedPosition.x += playerSpeed * deltaTime;

    // Resolve collision along X axis
    Rectangle newPlayerRectX = {proposedPosition.x, playerPosition.y, playerWidth, playerHeight};
    for (const auto& obj : objects) {
        if (obj.CheckCollision(newPlayerRectX)) {
            if (proposedPosition.x < obj.rect.x) {
                proposedPosition.x = obj.rect.x - playerWidth;  // Flush to the left
            } else if (proposedPosition.x > obj.rect.x) {
                proposedPosition.x = obj.rect.x + obj.rect.width;  // Flush to the right
            }
        }
    }

    // Resolve collision along Y axis
    Rectangle newPlayerRectY = {proposedPosition.x, proposedPosition.y, playerWidth, playerHeight};
    for (const auto& obj : objects) {
        if (obj.CheckCollision(newPlayerRectY)) {
            if (proposedPosition.y < obj.rect.y) {
                proposedPosition.y = obj.rect.y - playerHeight;  // Flush above
            } else if (proposedPosition.y > obj.rect.y) {
                proposedPosition.y = obj.rect.y + obj.rect.height;  // Flush below
            }
        }
    }

    // Update player position
    playerPosition = proposedPosition;

    // Keep the player within the screen boundaries
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if (playerPosition.x < 0) playerPosition.x = 0;
    if (playerPosition.x + playerWidth > screenWidth) playerPosition.x = screenWidth - playerWidth;
    if (playerPosition.y < 0) playerPosition.y = 0;
    if (playerPosition.y + playerHeight > screenHeight) playerPosition.y = screenHeight - playerHeight;
}

