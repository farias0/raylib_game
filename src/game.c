#include "raylib.h"

#include "player.h"
#include "bullet.h"

#define DEFAULT_PLAYER_STEP 2.0f
#define RUNNING_PLAYER_STEP 10.0f

#define BULLET_STEP -6.0f

int main(int argc, char **argv)
{
    float playerMovementStep = DEFAULT_PLAYER_STEP;

    const int screenWidth = 800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Space Invaders!");
    SetTargetFPS(60);

    { // Initialization
        InitializePlayer();
        InitializeBulletSystem();

        SetPlayerStartingPosition((Vector2){ (float)screenWidth/2, (float)screenHeight/2 });
    }


    // TODO remove it
    Bullet bullet;
    SetBulletStartingPosition(&bullet, (Vector2){ (float)screenWidth/3, (float)screenHeight/3 });


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        { // Game Update
            Vector2 playerDelta = { 0.0f, 0.0f };

            if (IsKeyDown(KEY_LEFT_SHIFT)) playerMovementStep = RUNNING_PLAYER_STEP;
            if (IsKeyReleased(KEY_LEFT_SHIFT)) playerMovementStep = DEFAULT_PLAYER_STEP;

            if (IsKeyDown(KEY_RIGHT) && (playerHitbox.x + playerHitbox.width) < screenWidth)
                playerDelta.x += playerMovementStep;
            if (IsKeyDown(KEY_LEFT) && playerHitbox.x > playerMovementStep)
                playerDelta.x -= playerMovementStep;
            if (IsKeyDown(KEY_UP) && playerHitbox.y > playerMovementStep)
                playerDelta.y -= playerMovementStep;
            if (IsKeyDown(KEY_DOWN) && (playerHitbox.y + playerHitbox.height) < screenHeight)
                playerDelta.y += playerMovementStep;

            UpdatePlayerPositionDelta(playerDelta);

            if (IsKeyDown(KEY_SPACE)) bullet.position.y = (float)screenWidth/3;
            UpdateBulletPositionDelta(&bullet, (Vector2){ 0.0f, BULLET_STEP });
        }

        { // Game Render
            BeginDrawing();
            ClearBackground(BLACK);
            // DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
            DrawPlayer();
            DrawBullet(&bullet);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}