#include <raylib.h>

#include "global.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define DEFAULT_PLAYER_STEP 2.0f
#define RUNNING_PLAYER_STEP 10.0f

#define HOLDING_FIRERATE 0.25f // How many seconds per shot when holding 'fire'

#define ENEMY_SPAWN_RATE 2.0f // How many seconds per enemy will spawn

int main(int argc, char **argv)
{
    bool isPaused = false;
    bool isPlayerDead = false;

    float playerMovementStep = DEFAULT_PLAYER_STEP;
    
    bool isHoldingShoot = false;
    double lastShotTime = -1;

    double lastEnemySpawn = 0;

    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    const Vector2 playerStartingPosition = (Vector2){ (float)screenWidth/2, (float)screenHeight/2 };

    InitWindow(screenWidth, screenHeight, "Space Invaders!");
    SetTargetFPS(60);

    { // Initialization
        InitializePlayer();
        InitializeBulletSystem();
        InitializeEnemySystem();

        SetPlayerStartingPosition(playerStartingPosition);
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        { // Game Update
            if (isPaused) {
                if (IsKeyPressed(KEY_ENTER)) {
                    isPaused = false;
                    isPlayerDead = false;
                }
                else goto render;
            }
            else if (IsKeyPressed(KEY_ENTER)) {
                isPaused = true;
            }

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
            } else if (IsKeyUp(KEY_SPACE)) isHoldingShoot = false;

            BulletsPositionTick();
            DestroyOffscreenBullets(0);

            if (GetTime() - lastEnemySpawn > ENEMY_SPAWN_RATE) {
                SpawnEnemy();
                lastEnemySpawn = GetTime();
            }

            EnemiesPositionTick(playerPosition);

            Enemy *dummyEnemy = 0; // Allows deleting while looping
            for (Enemy *enemy = EnemyList; enemy; enemy = enemy->next) {
                if (dummyEnemy) {
                    MemFree(dummyEnemy);
                    dummyEnemy = 0;
                } 
                if (CheckCollisionRecs(playerHitbox, enemy->hitbox)) {
                    isPlayerDead = true;
                    isPaused = true;
                    SetPlayerStartingPosition(playerStartingPosition);
                    DestroyAllBullets();
                    DestroyAllEnemies();
                    break;
                }
                for (Bullet *bullet = BulletList; bullet; bullet = bullet->next) {
                    if (CheckCollisionRecs(enemy->hitbox, bullet->hitbox)) {
                        dummyEnemy = MemAlloc(sizeof(Enemy));
                        dummyEnemy->next = enemy->next;
                        DestroyBullet(bullet);
                        DestroyEnemy(enemy);
                        enemy = dummyEnemy;
                    }
                }
            }
        }

render:
        { // Game Render
            BeginDrawing();
            ClearBackground(BLACK);
            DrawPlayer();
            DrawBullets();
            DrawEnemies();
            if (isPaused && !isPlayerDead) DrawText("PAUSE", screenWidth/2, screenHeight/2, 30, RAYWHITE);
            if (isPlayerDead) DrawText("YOU DIED", screenWidth/2, screenHeight/2, 60, RAYWHITE);
            if (IsKeyDown(KEY_SPACE)) DrawText("Shoot!", 10, 10, 20, RAYWHITE);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}