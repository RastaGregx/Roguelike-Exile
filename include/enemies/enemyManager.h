#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "enemies/enemy.h"
#include <vector>

// Update and manage the enemies in the game
void UpdateEnemies(std::vector<Enemy>& enemies, Vector2 playerPosition, float deltaTime, std::vector<Object>& objects);
void RemoveDeadEnemies(std::vector<Enemy>& enemies);

#endif
