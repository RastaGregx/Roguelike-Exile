#include "raylib.h"
#include <cstdlib>
#include <ctime>


int main() {
    // Virtual resolution (design resolution)
    const int virtualWidth = 800;
    const int virtualHeight = 600;

    // Set window to be resizable
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(virtualWidth, virtualHeight, "Virtual Resolution Example");

    // Set target FPS
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key

        // Calculate scaling factors for virtual resolution
        float scaleX = (float)GetScreenWidth() / virtualWidth;
        float scaleY = (float)GetScreenHeight() / virtualHeight;

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Apply virtual resolution scaling
        BeginScissorMode(0, 0, GetScreenWidth(), GetScreenHeight());
        DrawText("Scaled to Virtual Resolution", (int)(200 * scaleX), (int)(200 * scaleY), (int)(20 * scaleX), LIGHTGRAY);
        EndScissorMode();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

