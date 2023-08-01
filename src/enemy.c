#include <raylib.h>
#include <raymath.h>
#include <math.h>

#include "enemy.h"
#include "global.h"

#define ENEMY_SPEED 4.0f
#define ENEMY_SPAWN_RADIUS_FROM_PLAYER 250.0f

static Texture2D sprite;

Enemy *EnemyList;

static void syncHitboxWithPosition(Enemy *enemy) {
    enemy->hitbox.x = enemy->position.x;
    enemy->hitbox.y = enemy->position.y;
}

void InitializeEnemySystem() {
    sprite = LoadTexture("../assets/alien_small_green_1_a.png");
}

Enemy *SpawnEnemy(Vector2 playerPosition) {
    Enemy *enemy = MemAlloc(sizeof(Enemy));
    
    do {
        enemy->position =
            (Vector2){ GetRandomValue(0, SCREEN_WIDTH - ENEMY_WIDTH), GetRandomValue(0, SCREEN_HEIGHT - ENEMY_WIDTH) };
    } while (Vector2Distance(enemy->position, playerPosition) < ENEMY_SPAWN_RADIUS_FROM_PLAYER);
    enemy->hitbox.width = ENEMY_WIDTH;
    enemy->hitbox.height = ENEMY_WIDTH;
    syncHitboxWithPosition(enemy);

    if (!EnemyList) {
        EnemyList = enemy;
    } else {
        Enemy *lastEnemy = EnemyList;
        while (lastEnemy->next) lastEnemy = lastEnemy->next;
        enemy->previous = lastEnemy;
        lastEnemy->next = enemy;
    }

    return enemy;
}

void EnemiesPositionTick(Vector2 playerPosition) {
    Enemy *current = EnemyList;
    
    while (current) {
        float theta = Vector2LineAngle(current->position, playerPosition);
        current->position.x += cos(theta);
        current->position.y += sin(theta);
        syncHitboxWithPosition(current);

        current = current->next;
    }
}

void DestroyEnemy(Enemy *enemy) {
    if (enemy->previous) enemy->previous->next = enemy->next;
    if (enemy->next) enemy->next->previous = enemy->previous;
    
    if (EnemyList == enemy) EnemyList = enemy->next;

    MemFree(enemy);
}

void DestroyAllEnemies() {
    Enemy *current = EnemyList;

    while (current) {
        Enemy *next = current->next;
        MemFree(current);
        current = next;
    }

    EnemyList = 0;
}

void DrawEnemies() {
    Enemy *current = EnemyList;

    while (current) {
        DrawTextureEx(sprite, current->position, 0, ENEMY_SPRITE_SCALE, WHITE);
        current = current->next; 
    }
}