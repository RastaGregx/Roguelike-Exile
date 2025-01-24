#pragma once
#include <vector>
#include <memory>
#include "enemy.h"

class EnemyManager {
public:
    // Add a new enemy to the manager
    void AddEnemy(const std::shared_ptr<Enemy>& enemy);

    // Update all enemies
    void UpdateEnemies(Vector2 playerPosition, float deltaTime, const std::vector<Object>& objects, Player& player);

    // Draw all enemies
    void DrawEnemies() const;

    // Remove dead enemies from the list
    void RemoveDeadEnemies();

    // Clear all enemies (for resetting game)
    void ClearEnemies();

    // Get all enemies
    const std::vector<std::shared_ptr<Enemy>>& GetEnemies() const;

private:
    std::vector<std::shared_ptr<Enemy>> enemies;  // Store enemies
};
