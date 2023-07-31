#include <raylib.h>
#include "enemy.h"
#include "global.h"

static Texture2D sprite;

Enemy *EnemyList;

static void syncHitboxWithPosition(Enemy *enemy) {
    enemy->hitbox.x = enemy->position.x;
    enemy->hitbox.y = enemy->position.y;
}

void InitializeEnemySystem() {
    sprite = LoadTexture("../assets/alien_small_green_1_a.png");
}

Enemy *SpawnEnemy() {
    Enemy *enemy = MemAlloc(sizeof(Enemy));
    
    enemy->position = (Vector2){ GetRandomValue(0, SCREEN_WIDTH - ENEMY_WIDTH), GetRandomValue(0, SCREEN_HEIGHT - ENEMY_WIDTH) };
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

void EnemiesPositionTick() {
    Enemy* current = EnemyList;
    
    while (current) {
        current->position.y += -2.0f;
        syncHitboxWithPosition(current);

        current = current->next;
    }
}

void DrawEnemies() {
    Enemy* current = EnemyList;

    while (current) {
        DrawTextureEx(sprite, current->position, 0, ENEMY_SPRITE_SCALE, WHITE);
        current = current->next; 
    }
}