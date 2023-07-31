#include <raylib.h>
#include "player.h"

#define PLAYER_SPRITE_SCALE 5
#define PLAYER_WIDTH (float)(PLAYER_SPRITE_SCALE * 8) // sprite is 8x8 pixels

static Vector2 position = { 0.0f, 0.0f }; // Top left point of the player, from where the sprite will be drawn
static Texture2D sprite;

Rectangle playerHitbox = { 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH };

static void syncHitboxWithPosition() {
    playerHitbox.x = position.x;
    playerHitbox.y = position.y;
}

void InitializePlayer() {
    sprite = LoadTexture("../assets/player_center.png");
}

void SetPlayerStartingPosition(Vector2 pos) {
    position = pos;
    syncHitboxWithPosition();
}

void UpdatePlayerPositionDelta(Vector2 delta) {
    position.x += delta.x;
    position.y += delta.y;
    syncHitboxWithPosition();
}

void DrawPlayer() {
    DrawTextureEx(sprite, position, 0, PLAYER_SPRITE_SCALE, WHITE);
}