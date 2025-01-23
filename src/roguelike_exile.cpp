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
    const int screenWidth = 1920;
    const int screenHeight = 1070;

    InitWindow(screenWidth, screenHeight, "Roguelike Exile");
    SetTargetFPS(60);

    Font font = LoadFont("resources/fonts/modern.ttf");

    GameScreen currentScreen;

    bool isPlaying, playerDead;
    Vector2 playerPosition;
    Player player;
    Attack playerAttack;

    std::vector<Object> objects;
    std::vector<Enemy> enemies;

    InitGameState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies);
    InitPlayer(player, screenWidth / 2.0f, screenHeight / 2.0f, 300.0f, 45.0f, 45.0f, 50);

    Camera2D camera = { 0 };

    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.8f;

//Main game loop
while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    UpdateGameState(currentScreen, isPlaying, playerDead, playerPosition, objects, enemies, player);
    UpdatePlayerMovement(player, deltaTime, objects, camera);
    HandlePlayerInput(player, playerAttack, objects, deltaTime, camera);
    playerAttack.Update(deltaTime, enemies, objects);

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        it->Update(player.position, deltaTime, objects, player, enemies);
        if (!it->IsAlive()) {
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
    
    if (player.hp <= 0 && !playerDead) 
    {
        playerDead = true;
        std::cout << "Player has died.\n";
    }

    camera.target = player.position;

    BeginDrawing();
    ClearBackground(BLACK);

    if (currentScreen == GAMEPLAY) {
        BeginMode2D(camera);
        DrawGameplayScreen(objects, enemies, playerAttack, player.position, font, screenWidth, screenHeight);
        playerAttack.Draw();
        EndMode2D();
        
        DrawText(("Health: " + std::to_string(player.hp)).c_str(), 10, 10, 20, RAYWHITE);
        DrawText(("Position: (" + std::to_string((int)player.position.x) + ", " + std::to_string((int)player.position.y) + ")").c_str(), 10, 40, 20, RAYWHITE);
    }
    EndDrawing();
}
    UnloadFont(font);
    CloseWindow();
    return 0;
}
