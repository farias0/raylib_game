#ifndef _BULLET_H_INCLUDED_
#define _BULLET_H_INCLUDED_


#include <raylib.h>

#define BULLET_SPRITE_SCALE 3
#define BULLET_WIDTH (float)(BULLET_SPRITE_SCALE * 8) // sprite is 8x8 pixels

typedef struct Bullet {
    Rectangle hitbox;

    struct Bullet *next;
    struct Bullet *previous;
} Bullet;

extern Bullet *BulletList;

void InitializeBulletSystem();
Bullet *CreateBullet(Vector2 pos);
void BulletsPositionTick();
void DestroyBullet(Bullet *bullet);
void DestroyOffscreenBullets(int minY);
void DestroyAllBullets();
void DrawBullets();


#endif // _BULLET_H_INCLUDED_