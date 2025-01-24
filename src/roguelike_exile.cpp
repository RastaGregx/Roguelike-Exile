#include "raylib.h"

#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"

#include "enemies/enemyManager.h"
#include "enemies/enemy.h"
#include "enemies/tank.h"

#include "objects/object.h"

#include "utils/GameState.h"
#include "utils/InputControl.h"
#include "utils/DrawingUI.h"

#include <iostream>
#include <vector>
#include <raymath.h>

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1070;


    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);
    Image icon = LoadImage("build/assets_copy/assets/sprites/wisp.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    Font font = LoadFont("resources/fonts/modern.ttf");
    Texture2D sprite = LoadTexture("build/assets_copy/assets/sprites/wisp.png");

    GameScreen currentScreen;

    bool isPlaying, playerDead;
    Player player;
    Attack playerAttack;

    EnemyManager enemyManager;

    std::vector<Object> objects;
    Camera2D camera = { 100, 100 };


    camera.target = {player.position};
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    InitGameState(currentScreen, isPlaying, playerDead, player.position, objects, enemyManager);


while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    HandleStates(currentScreen, isPlaying, playerDead, player, player.position, objects, enemyManager, camera);
    UpdateGameState(currentScreen, isPlaying, playerDead, player.position, objects, enemyManager, player, camera);

    BeginDrawing();
    ClearBackground(BLACK);

    switch(currentScreen) {
        case TITLE:
            DrawTitleScreen(font, screenWidth, screenHeight);
            break;
        case GAMEPLAY: 
            UpdatePlayerMovement(player, deltaTime, objects, camera);
            HandlePlayerInput(player, playerAttack, objects, deltaTime, camera);

            BeginMode2D(camera);
            DrawGameplayScreen(objects, playerAttack, player.position, font, screenWidth, screenHeight, player);
            playerAttack.Draw();
            playerAttack.Update(deltaTime, enemyManager.GetEnemies(), objects);
            EndMode2D();
            
            DrawText(("Health: " + std::to_string(player.hp)).c_str(), 10, 10, 20, RAYWHITE);
            DrawText(("Position: (" + std::to_string((int)player.position.x) + ", " + std::to_string((int)player.position.y) + ")").c_str(), 10, 40, 20, RAYWHITE);
            break;
        case GAMEOVER:
            DrawGameOverScreen(font, screenWidth, screenHeight);
            break;
    }

    EndDrawing();
}
    UnloadFont(font);
    CloseWindow();
    return 0;
}
