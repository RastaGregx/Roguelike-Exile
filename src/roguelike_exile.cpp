#include "raylib.h"
#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"
#include "enemies/enemy.h" 
#include "object.h"
#include "map.h"
#include <vector>
#include <raymath.h>
#include <iostream>

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

int main() {

    const int screenWidth = 2560;
    const int screenHeight = 1340;  
    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);

    Font font = LoadFont("resources/fonts/modern.ttf");
    GameScreen currentScreen = TITLE;
    bool isPlaying = false;
    bool playerDead = false;

    Vector2 playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };
    Camera2D camera = { 0 };

    std::vector<Object> objects;
    std::vector<Enemy> enemies;
    Attack playerAttack; 

    objects.push_back(Object(500, 500, 200, 20));  // A wall at (500, 500) with size 200x20
    //objects.push_back(Object(800, 800, 200, 20));

    enemies.push_back(Enemy(Vector2{800, 400}, 100.0f, RED));

    // Main game loop
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime(); 

        // Debugging: Print the current state for debugging
        //printf("Current Screen: %d | Player Dead: %d\n", currentScreen, playerDead);

        // Handle screen transitions and game states
        if (currentScreen == TITLE) {
            if (IsKeyPressed(KEY_ENTER)) {
                //printf("Transitioning to GAMEPLAY\n");
                currentScreen = GAMEPLAY;
                isPlaying = true;
                playerDead = false;  // Reset player state when starting a new game
                playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };  // Reset player position
                enemies.clear();  // Clear existing enemies
                enemies.push_back(Enemy(Vector2{1000, 800}, 100.0f, RED));  // Add initial enemy
            }
        } 
        else if (currentScreen == GAMEOVER) {
            //printf("GAMEOVER state active.\n");

            if (IsKeyPressed(KEY_ENTER)) {
                //printf("KEY_ENTER detected. Transitioning to TITLE...\n");
                currentScreen = TITLE;

                // Reset game state
                isPlaying = false;
                playerDead = false;
                playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };
                enemies.clear();
                objects.clear();

                // Optionally reload objects and enemies for the new game
                objects.push_back(Object(500, 500, 200, 20));
                objects.push_back(Object(800, 800, 200, 20));
            }
        }

        // Handle gameplay logic
        if (currentScreen == GAMEPLAY && !playerDead) {
            // Debugging: Ensure the player is moving and is alive
            //printf("Player Position: (%.2f, %.2f) | Is Alive: %d\n", playerPosition.x, playerPosition.y, !playerDead);

            UpdatePlayerMovement(playerPosition, deltaTime, objects, camera);

            Vector2 mousePosition = GetMousePosition();
            Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
            Vector2 direction = Vector2Subtract(worldMousePosition, playerPosition);

            if (Vector2Length(direction) > 0) {
                direction = Vector2Normalize(direction);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                float speed = 500.0f; 
                Vector2 velocity = Vector2Scale(direction, speed); 
                playerAttack.Shoot(playerPosition, velocity, 10.0f, BLUE);
                //printf("Shooting projectile\n");
            }

            // Check if player collides with any enemy
            for (auto& enemy : enemies) {
                for (auto& enemy : enemies) {
                    enemy.Update(playerPosition, deltaTime, objects); // Pass objects for collision detection
                }


                // Check if enemy collides with player (simple collision detection)
                float distance = Vector2Distance(playerPosition, enemy.position);
                float combinedRadii = 25.0f + 20.0f;  // Assuming player is 50x50, enemy is 40x40

                if (distance < combinedRadii && !playerDead) {
                    //printf("Player collided with enemy\n");
                    playerDead = true;  // Set player death flag if collision occurs
                    currentScreen = GAMEOVER;  // Transition to GAMEOVER state
                    break;  // No need to check further enemies if the player is dead
                }
            }

            playerAttack.Update(deltaTime, objects);

            camera.target = (Vector2){ playerPosition.x + 20.0f, playerPosition.y + 20.0f };
            camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.8f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Debugging: Print the player's position
        //printf("Player Position: (%.2f, %.2f)\n", playerPosition.x, playerPosition.y);

        // Temporary: Debugging player position
        DrawText(TextFormat("Player Position: %.2f, %.2f", playerPosition.x, playerPosition.y), 10, 10, 20, DARKGRAY);

        BeginMode2D(camera);

        // Main screen logic for drawing
        if (currentScreen == TITLE) {
            DrawTextEx(font, "GAME MENU", Vector2{screenWidth / 2 - 150, screenHeight / 2 - 100}, 40, 2, BLACK);
            DrawTextEx(font, "Press ENTER to start", Vector2{screenWidth / 2 - 140, screenHeight / 2 + 20}, 20, 2, DARKGRAY);
        } else if (currentScreen == GAMEPLAY && !playerDead) {
            if (isPlaying) {
                DrawRectangleV(playerPosition, { 50, 50 }, BLUE);

                playerAttack.Draw();

                for (const auto& obj : objects) {
                    DrawRectangleRec(obj.rect, GREEN);
                }

                for (const auto& enemy : enemies) {
                    enemy.Draw();
                }
            }
        } else if (currentScreen == GAMEOVER || playerDead) {
            DrawTextEx(font, "GAME OVER", Vector2{screenWidth / 2 - 100, screenHeight / 2 - 50}, 40, 2, RED);
            DrawTextEx(font, "Press ENTER to return to menu", Vector2{screenWidth / 2 - 160, screenHeight / 2 + 30}, 20, 2, DARKGRAY);
        }

        EndMode2D();
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow(); 

    return 0;
}
