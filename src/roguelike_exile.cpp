#include "raylib.h"
#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"
#include "object.h"
#include "map.h"
#include <vector>
#include <raymath.h>

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

int main() {

    const int screenWidth = 2560;
    const int screenHeight = 1340;  
    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);

    Font font = LoadFont("resources/fonts/modern.ttf");
    GameScreen currentScreen = TITLE;
    bool isPlaying = false;

    Vector2 playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };
    Camera2D camera = { 0 };

    std::vector<Object> objects;
    Attack playerAttack; 

   // std::vector<Object> objects;
    objects.push_back(Object(500, 500, 200, 20));  // A wall at (500, 500) with size 200x20
    objects.push_back(Object(800, 800, 200, 20));  // Another wall



    // Main game loop
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime(); 

        if (currentScreen == TITLE) {
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = GAMEPLAY;
                isPlaying = true;
            }
        } else if (currentScreen == GAMEOVER) {
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = TITLE;
            }
        }

        if (currentScreen == GAMEPLAY) {
            UpdatePlayerMovement(playerPosition, deltaTime, objects, camera);

        // Get mouse position in screen coordinates
            Vector2 mousePosition = GetMousePosition();

            // Convert the mouse position to world coordinates (taking camera position into account)
            Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);

            // Calculate direction vector from player to mouse position (world coordinates)
            Vector2 direction = Vector2Subtract(worldMousePosition, playerPosition);

            // Normalize the direction to ensure consistent movement speed
            if (Vector2Length(direction) > 0) {
                direction = Vector2Normalize(direction);  // Normalize to get a unit vector
            }

            // Check for player attack input (e.g., left mouse button)
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                float speed = 500.0f;  // Speed of the projectile
                Vector2 velocity = Vector2Scale(direction, speed);  // Scale direction by speed
                playerAttack.Shoot(playerPosition, velocity, 10.0f, BLUE);  // Shoot projectile
            }

            // Update projectiles
            playerAttack.Update(deltaTime, objects);

            // Update camera position to follow the player
            camera.target = (Vector2){ playerPosition.x + 20.0f, playerPosition.y + 20.0f };

            // Adjust the offset to center the camera on the player
            camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.8f;  // Adjusted zoom for better view

            // Optional: Clamp camera position to ensure it stays within bounds
            float cameraMaxX = GetScreenWidth() / 2;
            float cameraMaxY = GetScreenHeight() / 2;
            // camera.target.x = Clamp(camera.target.x, cameraMaxX, screenWidth - cameraMaxX);
            // camera.target.y = Clamp(camera.target.y, cameraMaxY, screenHeight - cameraMaxY);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw camera bounds for debugging (green outline)
        DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 255, 0, 100});  // Camera bounds (green rectangle)

        // Temporary: Debugging player position
        DrawText(TextFormat("Player Position: %.2f, %.2f", playerPosition.x, playerPosition.y), 10, 10, 20, DARKGRAY);

        // Use the camera to follow the player
        BeginMode2D(camera);

        if (currentScreen == TITLE) {
            DrawTextEx(font, "GAME MENU", Vector2{screenWidth / 2 - 150, screenHeight / 2 - 100}, 40, 2, BLACK);
            DrawTextEx(font, "Press ENTER to start", Vector2{screenWidth / 2 - 140, screenHeight / 2 + 20}, 20, 2, DARKGRAY);
        } else if (currentScreen == GAMEPLAY) {
            if (isPlaying) {
                DrawRectangleV(playerPosition, { 50, 50 }, BLUE);  // A blue cube of 50x50

                // Draw projectiles
                playerAttack.Draw();

                // Render objects (if any) directly in world space
                for (const auto& obj : objects) {
                    DrawRectangleRec(obj.rect, GREEN);
                }
            }
        } else if (currentScreen == GAMEOVER) {
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
