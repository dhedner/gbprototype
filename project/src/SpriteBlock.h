#pragma once

UINT8 CheckBlockPush(Sprite* player, Sprite* block, UINT8 moves);

UINT8 GetBlockMoves(Sprite* spr);
UINT8 GetBlockPushTime(Sprite* spr);

void SetBlockVelocityX(Sprite* sprite, INT8 velocity_x);
void SetBlockVelocityY(Sprite* sprite, INT8 velocity_y);
void SetBlockMoves(Sprite* sprite, INT8 moves);
void SetBlockPushTime(Sprite* sprite, UINT8 push_time);

