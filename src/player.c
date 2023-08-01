#include <raylib.h>
#include "player.h"

#define PLAYER_SPRITE_SCALE 5
#define PLAYER_WIDTH (float)(PLAYER_SPRITE_SCALE * 8) // sprite is 8x8 pixels

#define PLAYER_SPEED_DEFAULT 4.0f
#define PLAYER_SPEED_FAST 8.0f

static Texture2D sprite;

Rectangle playerHitbox = { 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH };
Vector2 playerPosition = { 0.0f, 0.0f }; // Top left point of the player, from where the sprite will be drawn

static void syncHitboxWithPosition() {
    playerHitbox.x = playerPosition.x;
    playerHitbox.y = playerPosition.y;
}

void InitializePlayer() {
    sprite = LoadTexture("../assets/player_center.png");
}

void SetPlayerStartingPosition(Vector2 pos) {
    playerPosition = pos;
    syncHitboxWithPosition();
}

void MovePlayer(PlayerMovementType type, PlayerMovementDirection direction) {
    float amount = PLAYER_SPEED_DEFAULT;
    if (type == PLAYER_MOVEMENT_FAST) amount = PLAYER_SPEED_FAST;

    switch (direction) {
        case PLAYER_MOVEMENT_UP: playerPosition.y -= amount; break;
        case PLAYER_MOVEMENT_DOWN: playerPosition.y += amount; break;
        case PLAYER_MOVEMENT_LEFT: playerPosition.x -= amount; break;
        case PLAYER_MOVEMENT_RIGHT: playerPosition.x += amount; break;
    }

    syncHitboxWithPosition();
}

void DrawPlayer() {
    DrawTextureEx(sprite, playerPosition, 0, PLAYER_SPRITE_SCALE, WHITE);
}