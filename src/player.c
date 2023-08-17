#include <raylib.h>
#include "player.h"

#define PLAYER_SPRITE_SCALE 5
#define PLAYER_WIDTH (float)(PLAYER_SPRITE_SCALE * 8) // sprite is 8x8 pixels

#define PLAYER_SPEED_DEFAULT 4.0f
#define PLAYER_SPEED_FAST 8.0f

static Texture2D sprite;

Rectangle playerHitbox = { 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH };

void InitializePlayer() {
    sprite = LoadTexture("../assets/player_center.png");
}

void SetPlayerStartingPosition(Vector2 pos) {
    playerHitbox.x = pos.x;
    playerHitbox.y = pos.y;
}

void MovePlayer(PlayerMovementType type, PlayerMovementDirection direction) {
    float amount = PLAYER_SPEED_DEFAULT;
    if (type == PLAYER_MOVEMENT_FAST) amount = PLAYER_SPEED_FAST;

    switch (direction) {
        case PLAYER_MOVEMENT_UP: playerHitbox.y -= amount; break;
        case PLAYER_MOVEMENT_DOWN: playerHitbox.y += amount; break;
        case PLAYER_MOVEMENT_LEFT: playerHitbox.x -= amount; break;
        case PLAYER_MOVEMENT_RIGHT: playerHitbox.x += amount; break;
    }
}

void DrawPlayer() {
    DrawTextureEx(sprite, (Vector2){playerHitbox.x, playerHitbox.y}, 0, PLAYER_SPRITE_SCALE, WHITE);
}