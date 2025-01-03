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
        HandleShooting(player.position, playerAttack, direction);
        canShoot = false;  // Prevent additional shooting in the same frame
    }

    // Reset the cooldown after a small delay
    if (!canShoot) {
        canShoot = true;
    }
}


void HandleShooting(Vector2& playerPosition, Attack& playerAttack, Vector2 direction) {
    float speed = 500.0f; 
    Vector2 velocity = Vector2Scale(direction, speed); 

    std::cout << "Projectile velocity: " << velocity.x << ", " << velocity.y << std::endl;

    playerAttack.Shoot(playerPosition, velocity, 10.0f, BLUE);
}
