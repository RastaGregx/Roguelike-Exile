#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "raylib.h"
#include "objects/object.h"
#include "player/player.h"
#include <vector>

void UpdatePlayerMovement(Player &player, float deltaTime, const std::vector<Object>& objects, Camera2D &camera);

#endif
