#pragma once

typedef struct PLAYER_DATA
{
    UINT8 velocity_x;
    UINT8 velocity_y;
    UINT8 max_life;
    Sprite* sprite;
} PLAYER_DATA;

PLAYER_DATA* player;

UINT8 PlayerMove();
