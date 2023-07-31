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

void DestroyOffscreenBullets(int minY) {
    Bullet* current = BulletList;

    while (current) {
        if (current->hitbox.y < minY) {
            if (current->previous) current->previous->next = current->next;
            if (current->next) current->next->previous = current->previous;
            
            if (BulletList == current) BulletList = current->next;

            Bullet *next = current->next;
            MemFree(current);
            current = next;
        } else {
            current = current->next;
        }
    }
}

void DrawBullets() {
    Bullet* current = BulletList;

    while (current) {
        DrawTextureEx(sprite, current->position, 0, BULLET_SPRITE_SCALE, WHITE);
        current = current->next; 
    }
}