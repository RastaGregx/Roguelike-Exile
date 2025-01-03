#include "player/movement.h"
#include "raylib.h"
#include "objects/object.h"
#include "player/player.h"
#include <vector>

void UpdatePlayerMovement(Player &player, float deltaTime, const std::vector<Object>& objects, Camera2D &camera) {
    // Process movement
    Vector2 proposedPosition = player.position;

    if (IsKeyDown(KEY_W)) proposedPosition.y -= player.speed * deltaTime;
    if (IsKeyDown(KEY_S)) proposedPosition.y += player.speed * deltaTime;
    if (IsKeyDown(KEY_A)) proposedPosition.x -= player.speed * deltaTime;
    if (IsKeyDown(KEY_D)) proposedPosition.x += player.speed * deltaTime;

    // Resolve collision along X axis
    Rectangle newPlayerRectX = {proposedPosition.x, player.position.y, player.width, player.height};
    for (const auto& obj : objects) {
        if (obj.CheckCollision(newPlayerRectX)) {
            if (proposedPosition.x < obj.rect.x) {
                proposedPosition.x = obj.rect.x - player.width;  // Flush to the left
            } else if (proposedPosition.x > obj.rect.x) {
                proposedPosition.x = obj.rect.x + obj.rect.width;  // Flush to the right
            }
        }
    }

    // Resolve collision along Y axis
    Rectangle newPlayerRectY = {proposedPosition.x, proposedPosition.y, player.width, player.height};
    for (const auto& obj : objects) {
        if (obj.CheckCollision(newPlayerRectY)) {
            if (proposedPosition.y < obj.rect.y) {
                proposedPosition.y = obj.rect.y - player.height;  // Flush above
            } else if (proposedPosition.y > obj.rect.y) {
                proposedPosition.y = obj.rect.y + obj.rect.height;  // Flush below
            }
        }
    }

    // Update player position
    player.position = proposedPosition;

    // Keep the player within the screen boundaries
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if (player.position.x < 0) player.position.x = 0;
    if (player.position.x + player.width > screenWidth) player.position.x = screenWidth - player.width;
    if (player.position.y < 0) player.position.y = 0;
    if (player.position.y + player.height > screenHeight) player.position.y = screenHeight - player.height;

    // Update camera to follow the player
    camera.target = (Vector2){ player.position.x + player.width / 2.0f, player.position.y + player.height / 2.0f };
}
