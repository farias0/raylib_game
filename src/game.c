#include "raylib.h"

#include "player.h"

int main(int argc, char **argv)
{
    const int screenWidth = 800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Space Invaders!");
    SetTargetFPS(60);

    { // Initialization
        InitializePlayer();

        SetPlayerStartingPosition((Vector2){ (float)screenWidth/2, (float)screenHeight/2 });
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        { // Game Update
            Vector2 playerDelta = { 0.0f, 0.0f };
            if (IsKeyDown(KEY_RIGHT)) playerDelta.x += 2.0f;
            if (IsKeyDown(KEY_LEFT)) playerDelta.x -= 2.0f;
            if (IsKeyDown(KEY_UP)) playerDelta.y -= 2.0f;
            if (IsKeyDown(KEY_DOWN)) playerDelta.y += 2.0f;
            UpdatePlayerPositionDelta(playerDelta);
        }

        { // Game Render
            BeginDrawing();
            ClearBackground(RAYWHITE);
            // DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
            DrawPlayer();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}