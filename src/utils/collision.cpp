#include "utils/collision.h"
#include "raylib.h"  // Make sure to include necessary libraries
#include "enemies/enemy.h"
#include "player/attack.h"

// Function to check for collision between projectiles and enemies
bool CheckCollisionWithEnemies(Attack& playerAttack, std::vector<Enemy>& enemies) {
    for (auto& projectile : playerAttack.projectiles) {
        for (auto& enemy : enemies) {
            if (enemy.IsAlive() && CheckCollisionCircles(projectile.position, projectile.radius, enemy.position, 20.0f)) {
                enemy.TakeDamage(10);
                projectile.active = false;  // Set projectile inactive upon collision
                return true;  // Collision detected
            }
        }
    }
    return false;
}
