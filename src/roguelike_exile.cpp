#include "raylib.h"

#include "player/player.h"
#include "player/movement.h"
#include "player/attack.h"

#include "enemies/enemy.h"

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
    Image icon = LoadImage("../assets/sprites/wisp.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    Font font = LoadFont("resources/fonts/modern.ttf");
    Texture2D sprite = LoadTexture("../assets/sprites/ground.png");

    GameScreen currentScreen;

    bool isPlaying, playerDead;
    Player player;
    Attack playerAttack;

    std::vector<Object> objects;
    std::vector<std::shared_ptr<Enemy>> enemies;
    Camera2D camera = { 100, 100 };


    camera.target = {player.position};
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    InitGameState(currentScreen, isPlaying, playerDead, player.position, objects, enemies);
while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    UpdateGameState(currentScreen, isPlaying, playerDead, player.position, objects, enemies, player);

    UpdatePlayerMovement(player, deltaTime, objects, camera);
    HandlePlayerInput(player, playerAttack, objects, deltaTime, camera);

    playerAttack.Update(deltaTime, enemies, objects);

    if (player.hp <= 0 && !playerDead) 
    {
        playerDead = true;
        std::cout << "Player has died.\n";
    }

    Vector2 playerWorldPos = GetWorldToScreen2D(player.position, camera);

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        std::cout << "Position Passed to Enemy: (" 
                  << playerWorldPos.x << ", " << playerWorldPos.y << ")" << std::endl;
        (*it)->Update(playerWorldPos, deltaTime, objects, player, enemies);
        if (!(*it)->IsAlive()) { 
            it = enemies.erase(it);
        } else {
            ++it; 
        }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (currentScreen == GAMEPLAY) {
        BeginMode2D(camera);
        DrawGameplayScreen(objects, enemies, playerAttack, player.position, font, screenWidth, screenHeight, player);
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
