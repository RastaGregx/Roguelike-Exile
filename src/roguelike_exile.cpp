#include "raylib.h"

#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"

#include "enemies/enemy.h" 
#include "objects/object.h"
#include "map.h"

#include <vector>
#include <raymath.h>
#include <iostream>
#include <algorithm>


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

    // Main game loop
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime(); 

        // Handle screen transitions and game states
        if (currentScreen == TITLE) {
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = GAMEPLAY;
                isPlaying = true;
                playerDead = false;
                playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };
                enemies.clear();
                enemies.push_back(Enemy(Vector2{1000, 800}, 100.0f, RED, 50)); // 50 HP enemy  
                objects.push_back(Object(500, 500, 200, 20));
                objects.push_back(Object(800, 800, 200, 20));
            }
        } 

        else if (currentScreen == GAMEOVER) {
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = TITLE;

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

        if (currentScreen == GAMEPLAY && !playerDead) {
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

            for (auto& projectile : playerAttack.projectiles) {
            for (auto& enemy : enemies) {
                if (enemy.IsAlive() &&
                    CheckCollisionCircles(projectile.position, projectile.radius, enemy.position, 20.0f)) {
                    enemy.TakeDamage(10);
                    projectile.active = false;
                    printf("Enemy hit! Health: %d\n", enemy.health);
                }
            }
            }
            enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.IsAlive(); }),
            enemies.end()
            );

            for (auto& enemy : enemies) {
                for (auto& enemy : enemies) {
                    enemy.Update(playerPosition, deltaTime, objects);
                }


                float distance = Vector2Distance(playerPosition, enemy.position);
                float combinedRadii = 25.0f + 20.0f; 

                if (distance < combinedRadii && !playerDead) {
                    playerDead = true; 
                    currentScreen = GAMEOVER; 
                    break; 
                }
            }

            playerAttack.Update(deltaTime, enemies, objects);

            camera.target = (Vector2){ playerPosition.x + 20.0f, playerPosition.y + 20.0f };
            camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.8f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

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
