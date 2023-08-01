#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_


#include <raylib.h>

typedef enum PlayerMovementType {
    PLAYER_MOVEMENT_DEFAULT,
    PLAYER_MOVEMENT_FAST
} PlayerMovementType;

typedef enum PlayerMovementDirection {
    PLAYER_MOVEMENT_UP,
    PLAYER_MOVEMENT_DOWN,
    PLAYER_MOVEMENT_LEFT,
    PLAYER_MOVEMENT_RIGHT
} PlayerMovementDirection;

extern Vector2 playerPosition;
extern Rectangle playerHitbox;

void InitializePlayer();
void SetPlayerStartingPosition(Vector2 pos);
void MovePlayer(PlayerMovementType type, PlayerMovementDirection direction);
void DrawPlayer();


#endif // _PLAYER_H_INCLUDED_