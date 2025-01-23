// #include "enemies/fastEnemy.h"
// #include <cstdlib>

// FastEnemy::FastEnemy(Vector2 pos, int level)
//     : Enemy(pos, 150.0f, BLUE, 30 + (level * 5)) {
//     attackCooldown = 0.5f; // Faster attack rate
// }

// void FastEnemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player, std::vector<Enemy>& enemies) {
//     // Call base class Update for common behavior
//     Enemy::Update(playerPosition, deltaTime, objects, player, enemies);

//     // Add custom behavior for FastEnemy here
//     // Example: Randomize movement slightly to make it less predictable
//     if (std::rand() % 10 < 2) { // 20% chance per frame
//         position.x += ((std::rand() % 3) - 1) * 5.0f; // Random small jitter
//         position.y += ((std::rand() % 3) - 1) * 5.0f;
//     }
// }

// void FastEnemy::Draw() const {
//     // Unique appearance for FastEnemy
//     DrawCircleV(position, collisionRadius, Fade(color, 0.7f)); // Semi-transparent blue
// }
