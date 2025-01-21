#include "enemies/meleeEnemy.h"
#include "raymath.h"

MeleeEnemy::MeleeEnemy(Vector2 pos, float spd, int hp)
    : Enemy(pos, spd, RED, hp) {}

void MeleeEnemy::Update(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player) {
    // Custom logic for a melee enemy, like charging toward the player

    Vector2 direction = Vector2Subtract(playerPosition, position);
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
    }

    Vector2 potentialPosition = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));

    // Check for collisions and move accordingly (same logic as before)
    bool collidesWithWall = false;
    for (const auto& obj : objects) {
        if (obj.IsActive() && CheckCollisionCircleRec(potentialPosition, 20.0f, obj.rect)) {
            collidesWithWall = true;
            break;
        }
    }

    if (!collidesWithWall) {
        position = potentialPosition;
    }

    // Handle attack logic (e.g., damage player if close enough)
    float distance = Vector2Distance(position, player.position);
    float combinedRadius = (width / 2) + (player.width / 2);
    if (distance < combinedRadius) {
        ::TakeDamage(player, 10); // Inflict damage on player
    }
}
