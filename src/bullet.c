#include "raylib.h"

#include "bullet.h"


static Texture2D sprite;

Bullet *BulletList = '\0';


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
    bullet->previous = '\0';
    bullet->next = '\0';

    if (BulletList == '\0') {
        BulletList = bullet;
    } else {
        Bullet *lastBullet = BulletList;
        while (lastBullet->next != '\0') lastBullet = lastBullet->next;
        bullet->previous = lastBullet;
        lastBullet->next = bullet;
    }

    return bullet;
}

void UpdateBulletsPositionDelta(Vector2 delta) {
    Bullet* current = BulletList;
    
    while (current != '\0') {
        current->position.x += delta.x;
        current->position.y += delta.y;
        syncHitboxWithPosition(current);

        current = current->next;
    }
}

void DestroyOffscreenBullets(int minY) {
    Bullet* current = BulletList;

    while (current != '\0') {
        if (current->hitbox.y < minY) {
            if (current->previous != '\0') current->previous->next = current->next;
            if (current->next != '\0') current->next->previous = current->previous;
            
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

    while (current != '\0') {
        DrawTextureEx(sprite, current->position, 0, BULLET_SPRITE_SCALE, WHITE);
        current = current->next; 
    }
}