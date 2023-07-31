#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_


#include <raylib.h>

extern Vector2 playerPosition;
extern Rectangle playerHitbox;

void InitializePlayer();
void SetPlayerStartingPosition(Vector2 pos);
void UpdatePlayerPositionDelta(Vector2 delta);
void DrawPlayer();


#endif // _PLAYER_H_INCLUDED_