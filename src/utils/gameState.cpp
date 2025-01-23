#include "utils/GameState.h"
#include "objects/object.h"
#include "enemies/enemy.h"
#include "player/player.h"
#include "raylib.h"
#include <vector>

void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies) {
    currentScreen = TITLE;
    isPlaying = false;
    playerDead = false;
    playerPosition = { 1280, 670 };

    enemies.clear();
    objects.clear();
}

void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies, Player& player) {
    if (playerDead && currentScreen != GAMEOVER) {
        currentScreen = GAMEOVER;
        isPlaying = false;
        return;
    }

    if (currentScreen == TITLE) {
        HandleTitleState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies);
    } else if (currentScreen == GAMEOVER) {
        HandleGameOverState(currentScreen, isPlaying, playerDead, player, playerPosition, objects, enemies);
    }
}

void HandleTitleState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies) {
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GAMEPLAY;
        isPlaying = true;
        playerDead = false;
        playerPosition = { 1280, 670 };
        enemies.clear();
        objects.clear();

        int level = 5;

        enemies.push_back(Enemy::CreateEnemy(Vector2{ 1000, 800 }, level));
        enemies.push_back(Enemy::CreateEnemy(Vector2{ 900, 800 }, level));
        enemies.push_back(Enemy::CreateEnemy(Vector2{ 700, 800 }, level));
        enemies.push_back(Enemy::CreateEnemy(Vector2{ 600, 800 }, level));
        enemies.push_back(Enemy::CreateEnemy(Vector2{ 500, 800 }, level));

        objects.push_back(Object(500, 500, 200, 20));
    }
}

void HandleGameOverState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies) {
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = TITLE;
        isPlaying = false;
        playerDead = false;
        playerPosition = { 1280, 670 }; 
        objects.clear();
        enemies.clear();
        InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 45.0f, 45.0f, 50);
    }
}
