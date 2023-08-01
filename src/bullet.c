#include <raylib.h>
#include "bullet.h"

#define BULLET_STEP -6.0f

static Texture2D sprite;

Bullet *BulletList;

static void syncHitboxWithPosition(Bullet *bullet) {
    bullet->hitbox.x = bullet->position.x;
    bullet->hitbox.y = bullet->position.y;
}

void InitializeBulletSystem() {
    sprite = LoadTexture("../assets/shoot_a.png");
}

Bullet *CreateBullet(Vector2 pos) {
    Bullet *bullet = MemAlloc(sizeof(Bullet));
    
    bullet->position = pos;
    bullet->hitbox.width = BULLET_WIDTH;
    bullet->hitbox.height = BULLET_WIDTH;
    syncHitboxWithPosition(bullet);

    if (!BulletList) {
        BulletList = bullet;
    } else {
        Bullet *lastBullet = BulletList;
        while (lastBullet->next) lastBullet = lastBullet->next;
        bullet->previous = lastBullet;
        lastBullet->next = bullet;
    }

    return bullet;
}

void BulletsPositionTick() {
    Bullet* current = BulletList;
    
    while (current) {
        current->position.y += BULLET_STEP;
        syncHitboxWithPosition(current);

        current = current->next;
    }
}

void DestroyBullet(Bullet *bullet) {
    if (bullet->previous) bullet->previous->next = bullet->next;
    if (bullet->next) bullet->next->previous = bullet->previous;
    
    if (BulletList == bullet) BulletList = bullet->next;

    MemFree(bullet);
}

void DestroyOffscreenBullets(int minY) {
    Bullet *current = BulletList;

    while (current) {
        if (current->hitbox.y < minY) {
            Bullet *next = current->next;
            DestroyBullet(current);
            current = next;
        } else {
            current = current->next;
        }
    }
}

void DestroyAllBullets() {
    Bullet *current = BulletList;

    while (current) {
        Bullet *next = current->next;
        MemFree(current);
        current = next;
    }

    BulletList = 0;
}

void DrawBullets() {
    Bullet *current = BulletList;

    while (current) {
        DrawTextureEx(sprite, current->position, 0, BULLET_SPRITE_SCALE, WHITE);
        current = current->next; 
    }
}