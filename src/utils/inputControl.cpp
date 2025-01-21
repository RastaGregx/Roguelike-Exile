#include "utils/InputControl.h"
#include "player/player.h"
#include "raylib.h"

#include <iostream>

void HandlePlayerInput(Player& player, Attack& playerAttack, std::vector<Object>& objects, float deltaTime, Camera2D& camera) {
    static bool canShoot = true;  // Flag to control shooting cooldown

    // Update player movement (pass entire player object)
    UpdatePlayerMovement(player, deltaTime, objects, camera);

    // Handle mouse input for attacking
    Vector2 mousePosition = GetMousePosition();
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    Vector2 direction = Vector2Subtract(worldMousePosition, player.position);

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    // Only allow shooting if the cooldown is over
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canShoot) {
        playerAttack.Shoot(player.position, direction); // Use Attack's Shoot method
        canShoot = false;  // Prevent additional shooting in the same frame
    }

    // Reset the cooldown after a small delay
    if (!canShoot) {
        canShoot = true;
    }
}
