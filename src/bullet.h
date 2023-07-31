#ifndef _BULLET_H_INCLUDED_
#define _BULLET_H_INCLUDED_


#include "raylib.h"

typedef struct Bullet {
    Vector2 position;
    Rectangle hitbox;
} Bullet;

void InitializeBulletSystem();
void SetBulletStartingPosition(Bullet *bullet, Vector2 pos);
void UpdateBulletPositionDelta(Bullet *bullet, Vector2 delta);
void DrawBullet(Bullet *bullet);


#endif // _BULLET_H_INCLUDED_