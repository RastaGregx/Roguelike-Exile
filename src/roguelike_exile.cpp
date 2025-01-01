#include "raylib.h"
#include "player/movement.h"
#include "player/player.h"

enum GameScreen { TITLE, GAMEPLAY, GAMEOVER };

int main() {

    const int screenWidth = 2560;
    const int screenHeight = 1340;  
    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);

    Font font = LoadFont("resources/fonts/modern.ttf");
    GameScreen currentScreen = TITLE;
    bool isPlaying = false;

 //   Player player;
 //   InitPlayer(player, screenWidth / 2 - 25, screenHeight / 2 - 25, 200.0f);  // Initialize player

    Vector2 playerPosition = { screenWidth / 2 - 25, screenHeight / 2 - 25 };




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
            UpdatePlayerMovement(playerPosition, deltaTime);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == TITLE) {
            DrawTextEx(font, "GAME MENU", Vector2{screenWidth / 2 - 150, screenHeight / 2 - 100}, 40, 2, BLACK);
            DrawTextEx(font, "Press ENTER to start", Vector2{screenWidth / 2 - 140, screenHeight / 2 + 20}, 20, 2, DARKGRAY);
        } else if (currentScreen == GAMEPLAY) {
            if (isPlaying) {
                DrawRectangleV(playerPosition, { 50, 50 }, RED);  // A blue cube of 50x50
            }
        } else if (currentScreen == GAMEOVER) {
            DrawTextEx(font, "GAME OVER", Vector2{screenWidth / 2 - 100, screenHeight / 2 - 50}, 40, 2, RED);
            DrawTextEx(font, "Press ENTER to return to menu", Vector2{screenWidth / 2 - 160, screenHeight / 2 + 30}, 20, 2, DARKGRAY);
        }

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow(); 

    return 0;
}
