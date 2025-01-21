#include "raylib.h"
#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"
#include "enemies/enemy.h"
#include "objects/object.h"
#include "map.h"
#include "utils/GameState.h"
#include "utils/InputControl.h"
#include "utils/DrawingUI.h"
#include <iostream>
#include <vector>
#include <raymath.h>

int main() {
    const int screenWidth = 2560;
    const int screenHeight = 1340;
    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);

    Font font = LoadFont("resources/fonts/modern.ttf");
    GameScreen currentScreen;
    bool isPlaying, playerDead;
    Vector2 playerPosition;
    std::vector<Object> objects;
    std::vector<Enemy> enemies;
    Player player;
    Attack playerAttack;  // Attack system for the player
    Camera2D camera = { 0 };

    // Initialize game state and player
    InitGameState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies);
    InitPlayer(player, screenWidth / 2.0f, screenHeight / 2.0f, 300.0f, 45.0f, 45.0f, 50);

    // Camera configuration
    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.8f;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update game state and player
        UpdateGameState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies, player);
        UpdatePlayerMovement(player, deltaTime, objects, camera);

        // Handle player input and shooting
        HandlePlayerInput(player, playerAttack, objects, deltaTime, camera);

        // Update attack system (projectiles)
        playerAttack.Update(deltaTime, enemies, objects);  // Update the projectiles

        // Update camera
        camera.target = player.position;

        // Update enemies' movement and collision with player
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            it->Update(player.position, deltaTime, objects, player);  // Update the enemy

            // Check if the enemy is alive
            if (!it->IsAlive()) {  // Use IsAlive() to check if the enemy is dead
                it = enemies.erase(it);  // Remove enemy from the vector and update iterator
            } else {
                ++it;  // Move to the next enemy if the current one is still alive
            }
}


        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        if (!playerDead && currentScreen == GAMEPLAY) {
            UpdatePlayerMovement(player, deltaTime, objects, camera);
                Color textColor = RAYWHITE;

                std::string healthText = "Health: " + std::to_string(player.hp);
                DrawText(healthText.c_str(), 10, 10, 20, textColor); 

                std::string positionText = "Position: (" + std::to_string((int)player.position.x) + ", " + std::to_string((int)player.position.y) + ")";
                DrawText(positionText.c_str(), 10, 40, 20, textColor); 

        for (auto& enemy : enemies) {
                enemy.Update(player.position, deltaTime, objects, player);
        }

        if (player.hp <= 0) {
                playerDead = true;
            }
        }

        UpdateGameState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies, player);

        if (currentScreen == GAMEPLAY) {
            BeginMode2D(camera);
            DrawGameplayScreen(objects, enemies, playerAttack, player.position, font, screenWidth, screenHeight);

            playerAttack.Draw();  // Draw the active projectiles

            EndMode2D();
        }

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}
