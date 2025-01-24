#include "utils/GameState.h"
#include "objects/object.h"
#include "enemies/enemy.h"
#include "player/player.h"
#include "raylib.h"
#include <vector>
#include <iostream>

void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies) {
    currentScreen = TITLE;
    isPlaying = false;
    playerDead = false;
    playerPosition = { 100, 100 };

    enemies.clear();
    objects.clear();
}

void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies, Player& player, Camera2D& camera) {
    if (playerDead && currentScreen != GAMEOVER) {
        currentScreen = GAMEOVER;
        isPlaying = false;
        return;
    }

    for (auto& enemy : enemies) {
        // Pass the actual player world position, not screen position
        enemy->Update(player.position, GetFrameTime(), objects, player, enemies);
    }
}

void HandleStates(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, std::vector<std::shared_ptr<Enemy>>& enemies, Camera2D& camera) {
    if (currentScreen == TITLE) {
        if (IsKeyPressed(KEY_ENTER)) {
            currentScreen = GAMEPLAY;
            isPlaying = true;
            playerDead = false;
            playerPosition = { 0, 0 };
            objects.clear();
            enemies.clear();

            InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 16.0f, 16.0f, 50, "../assets/sprites/wisp.png");
            
            Vector2 enemyPosition = { 400, 400 };
            enemies.push_back(std::make_shared<Enemy>(enemyPosition, 100.0f, RED, 10));
            objects.push_back(Object(500, 500, 200, 20));
            objects.push_back(Object(500, 500, 20, 200));
        }
    } else if (currentScreen == GAMEOVER) {
        if (IsKeyPressed(KEY_ENTER)) {
            currentScreen = TITLE;
            isPlaying = false;
            playerDead = false;
            playerPosition = { 100, 100 }; 
            objects.clear();
            enemies.clear();
            InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 45.0f, 45.0f, 50, "../assets/sprites/wisp.png");
        }
    }
    for (auto& enemy : enemies) {
        // Convert enemy world position to screen position for drawing
        Vector2 enemyScreenPos = GetWorldToScreen2D(enemy->GetPosition(), camera);
        DrawCircleV(enemyScreenPos, 10, RED); // Example drawing
    }
}