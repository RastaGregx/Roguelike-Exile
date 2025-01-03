#ifndef COLLISION_H
#define COLLISION_H

#include "player/attack.h"
#include "enemies/enemy.h"

// Collision check for projectiles and enemies
bool CheckCollisionWithEnemies(Attack& playerAttack, std::vector<Enemy>& enemies);

#endif // COLLISION_H
