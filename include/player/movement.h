// movement.h
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "raylib.h"
#include <vector>
#include "objects/object.h"

void UpdatePlayerMovement(Vector2 &playerPosition, float deltaTime, const std::vector<Object>& objects, Camera2D camera);

#endif // MOVEMENT_H
