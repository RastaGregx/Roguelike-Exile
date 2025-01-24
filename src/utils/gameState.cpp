#include "utils/GameState.h"
#include "objects/object.h"
#include "enemies/enemy.h"
#include "enemies/enemyManager.h"
#include "enemies/tank.h"
#include "player/player.h"
#include "raylib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager) {
    currentScreen = TITLE;
    isPlaying = false;
    playerDead = false;
    playerPosition = { 100, 100 };

    objects.clear();
    enemyManager.ClearEnemies(); 
}

void UpdateGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager, Player& player, Camera2D& camera) {
    if (playerDead && currentScreen != GAMEOVER) {
        currentScreen = GAMEOVER;
        isPlaying = false;
        return;
    }


    enemyManager.UpdateEnemies(player.position, GetFrameTime(), objects, player);
    enemyManager.RemoveDeadEnemies();
}

void HandleStates(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, EnemyManager& enemyManager, Camera2D& camera) {
    if (currentScreen == TITLE) {
        if (IsKeyPressed(KEY_ENTER)) {
            currentScreen = GAMEPLAY;
            isPlaying = true;
            playerDead = false;
            playerPosition = { 0, 0 };
            objects.clear();

            enemyManager.ClearEnemies();

            InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 16.0f, 16.0f, 50, "build/assets_copy/assets/sprites/wisp.png");

            // Load enemy stats from JSON
            std::ifstream file("build/assets_copy/assets/enemy_stats.json");
            if (!file.is_open()) {
                std::cerr << "Failed to open enemy_stats.json" << std::endl;
                return;
            }

            nlohmann::json enemyStats;
            try {
                file >> enemyStats;
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
                return;
            }

            for (const auto& enemyData : enemyStats["enemies"]) {
                Vector2 position = { enemyData["position"]["x"], enemyData["position"]["y"] };
                float speed = enemyData["speed"];
                Color color = GREEN; 
                int health = enemyData["health"];
                float attackCooldown = enemyData["attackCooldown"];
                std::string texturePath = enemyData["texturePath"];  

                // Create enemy based on type
                std::shared_ptr<Enemy> enemy;
                if (enemyData["type"] == "Tank") {
                    // Pass the texture path to the Tank constructor
                    enemy = std::make_shared<Tank>(position, speed, color, health, attackCooldown, texturePath);
                }
                // Add more enemy types as needed

                enemyManager.AddEnemy(enemy);
            }

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
            enemyManager.ClearEnemies();
            InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 45.0f, 45.0f, 50, "build/assets_copy/assets/sprites/wisp.png");
        }
    }

    // Drawing all the enemies using EnemyManager
    for (const auto& enemy : enemyManager.GetEnemies()) {
        Vector2 enemyScreenPos = GetWorldToScreen2D(enemy->GetPosition(), camera);
        Color enemyColor = BLUE; 
        float enemySize = 10.0f; 

        // Check if the enemy is a Tank and set the color and size
        if (std::shared_ptr<Tank> tank = std::dynamic_pointer_cast<Tank>(enemy)) {
            enemyColor = GREEN;
            enemySize = 20.0f; // Larger size for tanks
            if (tank->hasTexture()) {
                DrawTextureEx(tank->getTexture(),enemyScreenPos, 0.0f, 2.0f, WHITE);
            } else {
                DrawCircleV(enemyScreenPos, enemySize, enemyColor);
            }
        } else {
            DrawCircleV(enemyScreenPos, enemySize, enemyColor);
        }
    }
}

