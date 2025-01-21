#include "player/player.h"
#include "enemies/enemymanager.h"
#include "raymath.h"
#include "enemies/enemy.h"
#include <algorithm>

// Update enemies' state based on the player position
void UpdateEnemies(std::vector<Enemy>& enemies, Vector2 playerPosition, float deltaTime, std::vector<Object>& objects, Player& player) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].Update(playerPosition, deltaTime, objects, player, enemies);
    }
}

// Remove dead enemies from the list
void RemoveDeadEnemies(std::vector<Enemy>& enemies) {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.IsAlive(); }),
        enemies.end()
    );
}
