#include "enemies/enemyManager.h"
#include  <algorithm>

void EnemyManager::AddEnemy(const std::shared_ptr<Enemy>& enemy) {
    enemies.push_back(enemy);  // Add enemy to the list
}

void EnemyManager::UpdateEnemies(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player) {
    for (auto& enemy : enemies) {
        if (enemy->IsAlive()) {  // Update only alive enemies
            enemy->Update(playerPosition, deltaTime, objects, player, enemies);
        }
    }
}

void EnemyManager::RemoveDeadEnemies() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), 
            [](const std::shared_ptr<Enemy>& enemy) { return !enemy->IsAlive(); }),
        enemies.end()
    );
}

void EnemyManager::ClearEnemies() {
    enemies.clear();  // Clear the list of enemies
}

const std::vector<std::shared_ptr<Enemy>>& EnemyManager::GetEnemies() const {
    return enemies;  // Return the list of enemies
}
