#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "objects/object.h"
#include "enemies/enemy.h"
#include <vector>
#include "raylib.h"

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

// Function declarations
void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies);
void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies, Player& player);
void HandleStates(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies);

#endif