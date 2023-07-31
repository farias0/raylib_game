#include "raylib.h"

#include "bullet.h"


#define BULLET_SPRITE_SCALE 3
#define BULLET_WIDTH (float)(BULLET_SPRITE_SCALE * 8) // sprite is 8x8 pixels


static Texture2D sprite;


static void syncHitboxWithPosition(Bullet *bullet) {
    bullet->hitbox.x = bullet->position.x;
    bullet->hitbox.y = bullet->position.y;
}


void InitializeBulletSystem() {
    sprite = LoadTexture("../assets/shoot_a.png");
}

void SetBulletStartingPosition(Bullet *bullet, Vector2 pos) {
    bullet->position = pos;
    bullet->hitbox.width = BULLET_WIDTH;
    bullet->hitbox.height = BULLET_WIDTH;
    syncHitboxWithPosition(bullet);
}

void UpdateBulletPositionDelta(Bullet *bullet, Vector2 delta) {
    bullet->position.x += delta.x;
    bullet->position.y += delta.y;
    syncHitboxWithPosition(bullet);
}

void DrawBullet(Bullet *bullet) {
    DrawTextureEx(sprite, bullet->position, 0, BULLET_SPRITE_SCALE, WHITE);
}