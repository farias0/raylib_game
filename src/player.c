#include <raylib.h>

#include "player.h"

static Vector2 position = { 0.0f, 0.0f };
static Texture2D sprite;

void InitializePlayer() {
    sprite = LoadTexture("../assets/player_center.png");
}

void SetPlayerStartingPosition(Vector2 pos) {
    position = pos;
}

void UpdatePlayerPositionDelta(Vector2 pos) {
    position.x += pos.x;
    position.y += pos.y;
}

void DrawPlayer() {
    DrawTextureEx(sprite, position, 0, 5, WHITE);
}