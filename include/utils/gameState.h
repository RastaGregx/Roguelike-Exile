#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "objects/object.h"
#include "enemies/enemy.h"
#include <vector>
#include "raylib.h"

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

// Function declarations
void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies);
void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies, Player& player);
void HandleTitleState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies);
void HandleGameOverState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies);

#endif