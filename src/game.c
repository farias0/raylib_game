#include "raylib.h"

#include "player.h"
#include "bullet.h"

#define DEFAULT_PLAYER_STEP 2.0f
#define RUNNING_PLAYER_STEP 10.0f

#define BULLET_STEP -6.0f
#define HOLDING_FIRERATE 0.25f // How many shots per seconds when holding 'fire'

int main(int argc, char **argv)
{
    float playerMovementStep = DEFAULT_PLAYER_STEP;
    
    bool isHoldingShoot = false;
    double lastShotTime = -1;

    const int screenWidth = 800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Space Invaders!");
    SetTargetFPS(60);

    { // Initialization
        InitializePlayer();
        InitializeBulletSystem();

        SetPlayerStartingPosition((Vector2){ (float)screenWidth/2, (float)screenHeight/2 });
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        { // Game Update
            Vector2 playerDelta = { 0.0f, 0.0f };

            if (IsKeyDown(KEY_LEFT_SHIFT)) playerMovementStep = RUNNING_PLAYER_STEP;
            else playerMovementStep = DEFAULT_PLAYER_STEP;

            if (IsKeyDown(KEY_RIGHT) && (playerHitbox.x + playerHitbox.width) < screenWidth)
                playerDelta.x += playerMovementStep;
            if (IsKeyDown(KEY_LEFT) && playerHitbox.x > playerMovementStep)
                playerDelta.x -= playerMovementStep;
            if (IsKeyDown(KEY_UP) && playerHitbox.y > playerMovementStep)
                playerDelta.y -= playerMovementStep;
            if (IsKeyDown(KEY_DOWN) && (playerHitbox.y + playerHitbox.height) < screenHeight)
                playerDelta.y += playerMovementStep;

            UpdatePlayerPositionDelta(playerDelta);

            if (IsKeyDown(KEY_SPACE) && (!isHoldingShoot || GetTime() - lastShotTime > HOLDING_FIRERATE)) {
                CreateBullet((Vector2){ playerHitbox.x + (playerHitbox.width - BULLET_WIDTH) / 2, playerHitbox.y });
                lastShotTime = GetTime();
                isHoldingShoot = true;
            } else if (IsKeyUp(KEY_SPACE)) {
                isHoldingShoot = false;
            };
            UpdateBulletsPositionDelta((Vector2){ 0.0f, BULLET_STEP });
            DestroyOffscreenBullets(0);
        }

        { // Game Render
            BeginDrawing();
            ClearBackground(BLACK);
            if (IsKeyDown(KEY_SPACE)) DrawText("Shoot!", 10, 10, 20, RAYWHITE);
            DrawPlayer();
            DrawBullets();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}