#include <raylib.h>

#include "player.h"

static Vector2 position = { 0.0f, 0.0f };

void SetPlayerStartingPosition(Vector2 pos) {
    position = pos;
}

void UpdatePlayerPositionDelta(Vector2 pos) {
    position.x += pos.x;
    position.y += pos.y;
}

void DrawPlayer() {
    DrawCircleV(position, 10, MAROON);
}