#include "utils/InputControl.h"
#include "player/player.h"
#include "raylib.h"

#include <iostream>

void HandlePlayerInput(Player& player, Attack& playerAttack, std::vector<Object>& objects, float deltaTime, Camera2D& camera) {
    static bool canShoot = true;
    float shootCooldown = 0.2f;
    static float shootTimer = 0.0f;

    UpdatePlayerMovement(player, deltaTime, objects, camera);

    Vector2 mousePosition = GetMousePosition();
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    Vector2 direction = Vector2Subtract(worldMousePosition, player.position);

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    if (!canShoot) {
        shootTimer += GetFrameTime(); 
    if (shootTimer >= shootCooldown) {
        canShoot = true;
        shootTimer = 0.0f;
    }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canShoot) {
        playerAttack.Shoot(player.position, direction);
        canShoot = false;
    }

}
