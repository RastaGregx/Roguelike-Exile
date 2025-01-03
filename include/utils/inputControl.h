#ifndef INPUTCONTROL_H
#define INPUTCONTROL_H

#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"
#include "enemies/enemy.h"
#include "objects/object.h"
#include <vector>
#include "raymath.h"

// Handle player movement input and attack
void HandlePlayerInput(Player& player, Attack& playerAttack, std::vector<Object>& objects, float deltaTime, Camera2D& camera);
void HandleShooting(Vector2& playerPosition, Attack& playerAttack, Vector2 direction);

#endif
