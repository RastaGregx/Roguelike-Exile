#include "utils/GameState.h"
#include "objects/object.h"
#include "enemies/enemy.h"
#include "enemies/meleeEnemy.h"
#include "player/player.h"
#include "raylib.h"
#include <vector>

void InitGameState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies) {
    currentScreen = TITLE;
    isPlaying = false;
    playerDead = false;
    playerPosition = { 1280, 670 }; // Center of screen by default

    // Clear enemies and objects at start
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
        playerPosition = { 1280, 670 }; // Reset player position
        enemies.push_back(Enemy(Vector2{ 1000, 800 }, 100.0f, RED, 50)); // Example enemy
        enemies.push_back(MeleeEnemy(Vector2{ 900, 800 }, 50.0f, 100)); // Example derived enemy
        objects.push_back(Object(500, 500, 200, 20)); // Example object
    }
}

void HandleGameOverState(GameScreen& currentScreen, bool& isPlaying, bool& playerDead, Player& player, Vector2& playerPosition, std::vector<Object>& objects, std::vector<Enemy>& enemies) {
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = TITLE;  // Transition to title screen
        isPlaying = false;      // Stop gameplay logic
        playerDead = false;     // Reset the player death state
        playerPosition = { 1280, 670 }; // Reset player position
        objects.clear();        // Clear objects
        enemies.clear();        // Clear enemies
        InitPlayer(player, playerPosition.x, playerPosition.y, 300.0f, 45.0f, 45.0f, 50); // Reinitialize player
    }
}
