// #include "utils/collision.h"
// #include "raymath.h"
// #include "enemies/enemy.h"
// #include "player/attack.h"

// bool CheckCollisionWithEnemies(Attack& playerAttack, std::vector<Enemy>& enemies) {
//     for (auto& projectile : playerAttack.projectiles) {
//         for (auto& enemy : enemies) {
//             if (enemy.IsAlive() && CheckCollisionCircles(projectile.position, projectile.radius, enemy.position, 20.0f)) {
//                 enemy.TakeDamage(10);
//                 projectile.active = false;
//                 return true;
//             }
//         }
//     }
//     return false;
// }


