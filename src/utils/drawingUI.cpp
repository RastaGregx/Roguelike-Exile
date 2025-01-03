#include "utils/DrawingUI.h"
#include "raylib.h"

void DrawTitleScreen(Font font, int screenWidth, int screenHeight) {
    DrawTextEx(font, "GAME MENU", 
               Vector2{ static_cast<float>(screenWidth) / 2 - 150.0f, static_cast<float>(screenHeight) / 2 - 100.0f }, 
               40.0f, 2.0f, BLACK);
    DrawTextEx(font, "Press ENTER to start", 
               Vector2{ static_cast<float>(screenWidth) / 2 - 140.0f, static_cast<float>(screenHeight) / 2 + 20.0f }, 
               20.0f, 2.0f, DARKGRAY);
}

void DrawGameplayScreen(const std::vector<Object>& objects, const std::vector<Enemy>& enemies, const Attack& playerAttack, Vector2 playerPosition, Font font, int screenWidth, int screenHeight) {
    DrawRectangleV(playerPosition, { 50.0f, 50.0f }, BLUE);
    playerAttack.Draw();

    for (const auto& obj : objects) {
        DrawRectangleRec(obj.rect, GREEN);
    }

    for (const auto& enemy : enemies) {
        enemy.Draw();
    }
}

void DrawGameOverScreen(Font font, int screenWidth, int screenHeight) {
    DrawTextEx(font, "GAME OVER", 
               Vector2{ static_cast<float>(screenWidth) / 2 - 100.0f, static_cast<float>(screenHeight) / 2 - 50.0f }, 
               40.0f, 2.0f, RED);
    DrawTextEx(font, "Press ENTER to return to menu", 
               Vector2{ static_cast<float>(screenWidth) / 2 - 160.0f, static_cast<float>(screenHeight) / 2 + 30.0f }, 
               20.0f, 2.0f, DARKGRAY);
}
