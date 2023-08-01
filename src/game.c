#include <raylib.h>
#include <stdio.h>

#include "global.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define HOLDING_FIRERATE 0.25f // How many seconds per shot when holding 'fire'

#define DEFAULT_ENEMY_SPAWN_RATE 2.0f // How many seconds for an enemy to spawn
#define ENEMY_SPAWN_RATE_STEP 0.05f
#define MAX_ENEMY_SPAWN_RATE 0.3f

typedef struct GameState {
    bool isPaused;
    bool isPlayerDead;

    unsigned long score;
    bool isMaxDifficulty;

    float enemySpawnRate;

    PlayerMovementType playerMovementType;

    double lastShotTime;
    double lastEnemySpawn;
} GameState;

void resetGameState(GameState *state) {
    state->isPaused = false;
    state->isPlayerDead = false;

    state->score = 0;
    state->isMaxDifficulty = false;

    state->enemySpawnRate = DEFAULT_ENEMY_SPAWN_RATE;
    state->playerMovementType = PLAYER_MOVEMENT_DEFAULT;

    state->lastShotTime = -1;
    state->lastEnemySpawn = -1;

    SetPlayerStartingPosition((Vector2){ (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2 });
    DestroyAllBullets();
    DestroyAllEnemies();
}

int main(int argc, char **argv)
{
    GameState state;

    Color scoreColor;
    char scoreText[30];
    
    bool isHoldingShoot = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders!");
    SetTargetFPS(60);

    { // Initialization
        InitializePlayer();
        InitializeBulletSystem();
        InitializeEnemySystem();

        resetGameState(&state);
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        { // Game Update

            // Game State
            if (state.isPaused) {
                if (IsKeyPressed(KEY_ENTER)) {
                    if (state.isPlayerDead) {
                        resetGameState(&state);
                    } else {
                        state.isPaused = false;
                    }
                }
                else goto render;
            }
            else if (IsKeyPressed(KEY_ENTER)) {
                state.isPaused = true;
            }

            // Player
            Vector2 playerDelta = { 0.0f, 0.0f };

            if (IsKeyDown(KEY_LEFT_SHIFT)) state.playerMovementType = PLAYER_MOVEMENT_FAST;
            else state.playerMovementType = PLAYER_MOVEMENT_DEFAULT;

            if (IsKeyDown(KEY_RIGHT) && (playerHitbox.x + playerHitbox.width) < SCREEN_WIDTH)
                MovePlayer(state.playerMovementType, PLAYER_MOVEMENT_RIGHT);
            if (IsKeyDown(KEY_LEFT) && playerHitbox.x > 0)
                MovePlayer(state.playerMovementType, PLAYER_MOVEMENT_LEFT);
            if (IsKeyDown(KEY_UP) && playerHitbox.y > 0)
                MovePlayer(state.playerMovementType, PLAYER_MOVEMENT_UP);
            if (IsKeyDown(KEY_DOWN) && (playerHitbox.y + playerHitbox.height) < SCREEN_HEIGHT)
                MovePlayer(state.playerMovementType, PLAYER_MOVEMENT_DOWN);

            // Bullets
            if (IsKeyDown(KEY_SPACE) && (!isHoldingShoot || GetTime() - state.lastShotTime > HOLDING_FIRERATE)) {
                CreateBullet((Vector2){ playerHitbox.x + (playerHitbox.width - BULLET_WIDTH) / 2, playerHitbox.y });
                state.lastShotTime = GetTime();
                isHoldingShoot = true;
            } else if (IsKeyUp(KEY_SPACE)) isHoldingShoot = false;

            BulletsPositionTick();
            DestroyOffscreenBullets(0);

            // Enemies
            if (GetTime() - state.lastEnemySpawn > state.enemySpawnRate) {
                SpawnEnemy(playerPosition);
                state.lastEnemySpawn = GetTime();
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
                    state.isPlayerDead = true;
                    state.isPaused = true;
                    break;
                }

                for (Bullet *bullet = BulletList; bullet; bullet = bullet->next) {
                    if (CheckCollisionRecs(enemy->hitbox, bullet->hitbox)) {
                        dummyEnemy = MemAlloc(sizeof(Enemy));
                        dummyEnemy->next = enemy->next;
                        DestroyBullet(bullet);
                        DestroyEnemy(enemy);
                        enemy = dummyEnemy;
                        state.score += 10;
                        if (state.enemySpawnRate > MAX_ENEMY_SPAWN_RATE) state.enemySpawnRate -= ENEMY_SPAWN_RATE_STEP;
                        else state.isMaxDifficulty = true;
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

            if (state.isPaused && !state.isPlayerDead) DrawText("PAUSE", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 30, RAYWHITE);
            if (state.isPlayerDead) DrawText("YOU DIED", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 60, RAYWHITE);

            sprintf(scoreText, "Score: %lu", state.score);
            if (state.isMaxDifficulty) scoreColor = RED;
            else scoreColor = RAYWHITE;
            DrawText(scoreText, 10, 10, 20, scoreColor);

            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}