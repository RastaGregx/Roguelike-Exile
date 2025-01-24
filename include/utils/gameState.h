#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "objects/object.h"
#include "enemies/enemy.h"
#include "enemies/enemyManager.h"
#include "player/player.h"
#include <vector>
#include "raylib.h"

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

// Function declarations
void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager);
void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager, Player& player, Camera2D& camera);
void HandleStates(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager, Camera2D& camera);

#endif
