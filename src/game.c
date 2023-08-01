#include <raylib.h>
#include <stdio.h>

#include "global.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define DEFAULT_PLAYER_STEP 4.0f
#define RUNNING_PLAYER_STEP 8.0f

#define HOLDING_FIRERATE 0.25f // How many seconds per shot when holding 'fire'

#define DEFAULT_ENEMY_SPAWN_RATE 2.0f // How many seconds for an enemy to spawn
#define ENEMY_SPAWN_RATE_STEP 0.05f
#define MAX_ENEMY_SPAWN_RATE 0.3f

int main(int argc, char **argv)
{
    bool isPaused = false;
    bool isPlayerDead = false;

    unsigned long score = 0;
    char scoreText[30];
    bool isMaxDifficulty = false;

    float enemySpawnRate = DEFAULT_ENEMY_SPAWN_RATE;

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

            // Game State
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

            // Player
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

            // Bullets
            if (IsKeyDown(KEY_SPACE) && (!isHoldingShoot || GetTime() - lastShotTime > HOLDING_FIRERATE)) {
                CreateBullet((Vector2){ playerHitbox.x + (playerHitbox.width - BULLET_WIDTH) / 2, playerHitbox.y });
                lastShotTime = GetTime();
                isHoldingShoot = true;
            } else if (IsKeyUp(KEY_SPACE)) isHoldingShoot = false;

            BulletsPositionTick();
            DestroyOffscreenBullets(0);

            // Enemies
            if (GetTime() - lastEnemySpawn > enemySpawnRate) {
                SpawnEnemy(playerPosition);
                lastEnemySpawn = GetTime();
            }

            EnemiesPositionTick(playerPosition);

            // Collision
            Enemy *dummyEnemy = 0; // Allows deleting while looping
            for (Enemy *enemy = EnemyList; enemy; enemy = enemy->next) {

                if (dummyEnemy) {
                    MemFree(dummyEnemy);
                    dummyEnemy = 0;
                } 

                if (CheckCollisionRecs(playerHitbox, enemy->hitbox)) {
                    isPlayerDead = true;
                    isPaused = true;
                    score = 0;
                    isMaxDifficulty = false;
                    enemySpawnRate = DEFAULT_ENEMY_SPAWN_RATE;
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
                        score += 10;
                        if (enemySpawnRate > MAX_ENEMY_SPAWN_RATE) enemySpawnRate -= ENEMY_SPAWN_RATE_STEP;
                        else isMaxDifficulty = true;
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

            sprintf(scoreText, "Score: %lu", score);
            Color scoreColor = RAYWHITE;
            if (isMaxDifficulty) scoreColor = RED;
            DrawText(scoreText, 10, 10, 20, scoreColor);

            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}