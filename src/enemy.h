#ifndef _ENEMY_H_INCLUDED_
#define _ENEMY_H_INCLUDED_


#include <raylib.h>

#define ENEMY_SPRITE_SCALE 4
#define ENEMY_WIDTH (float)(ENEMY_SPRITE_SCALE * 8) // sprite is 8x8 pixels

typedef struct Enemy {
    Rectangle hitbox;

    struct Enemy *next;
    struct Enemy *previous;
} Enemy;

extern Enemy *EnemyList;

void InitializeEnemySystem();
Enemy *SpawnEnemy(Vector2 playerPosition);
void EnemiesPositionTick(Vector2 playerPosition);
void DestroyEnemy(Enemy *enemy);
void DestroyAllEnemies();
void DrawEnemies();


#endif // _ENEMY_H_INCLUDED_