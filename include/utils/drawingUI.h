#ifndef DRAWINGUI_H
#define DRAWINGUI_H

#include "raylib.h"
#include "player/player.h"
#include "player/attack.h"
#include "objects/object.h"
#include "enemies/enemy.h"
#include <vector>

void DrawTitleScreen(Font font, int screenWidth, int screenHeight);
void DrawGameplayScreen(const std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>> enemies, const Attack& playerAttack, Vector2 playerPosition, Font font, int screenWidth, int screenHeight, const Player& player);
void DrawGameOverScreen(Font font, int screenWidth, int screenHeight);

#endif
