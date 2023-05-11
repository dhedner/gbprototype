#include "Banks/SetAutoBank.h"
#include "ZGBMain.h" // For access to all sprite types

#include "SpriteBlock.h"
#include "SpriteManager.h"
#include "SpritePlayer.h"

typedef struct BLOCK_DATA
{
    INT8 velocity_x;
    INT8 velocity_y;
    UINT8 push_time;
    UINT8 moves;
} BLOCK_DATA;

UINT8 GetBlockMoves(Sprite* sprite)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    return block->moves;
}

UINT8 GetBlockPushTime(Sprite* sprite)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    return block->push_time;
}

void SetBlockVelocityX(Sprite* sprite, INT8 velocity_x)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    block->velocity_x = velocity_x;
}

void SetBlockVelocityY(Sprite* sprite, INT8 velocity_y)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    block->velocity_y = velocity_y;
}

void SetBlockMoves(Sprite* sprite, INT8 moves)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    block->moves = moves;
}

void SetBlockPushTime(Sprite* sprite, UINT8 push_time)
{
    BLOCK_DATA* block = (BLOCK_DATA*)sprite->custom_data;
    block->push_time = push_time;
}

void START()
{
    BLOCK_DATA* block = (BLOCK_DATA*)THIS->custom_data;

    block->velocity_x = 0;
    block->velocity_y = 0;
    block->push_time = 100;
    block->moves = 0;
}

void UPDATE()
{
    BLOCK_DATA* block = (BLOCK_DATA*)THIS->custom_data;
    TranslateSprite(THIS, block->velocity_x << delta_time, block->velocity_y << delta_time);

    if ((THIS->x & 0x0F) == 0)
    {
        if (block->velocity_x != 0)
        {
            block->moves--;
            block->velocity_x = 0;
        }
    }

    if ((THIS->y & 0x0F) == 0)
    {
        if (block->velocity_y != 0)
        {
            block->moves--;
            block->velocity_y = 0;
        }
    }
}

void DESTROY()
{
}

void WaitforPushTimer()
{
    UINT8 numloops = GetBlockPushTime(THIS);

    for (UINT8 i = 0; i < numloops; i++)
    {
        SetBlockPushTime(THIS, GetBlockPushTime(THIS) - 1);
    }
}

UINT8 CheckBlockPush(Sprite* player, Sprite* block, UINT8 moves)
{
    INT8 direction_x = GetPlayerMovementDirectionX(player);
    INT8 direction_y = GetPlayerMovementDirectionY(player);

    if (moves > 0)
    {
        if (direction_x == 1 && direction_y == 0)
        {
            WaitforPushTimer();
            SetBlockVelocityX(block, 1);
        }
        else if (direction_x == -1 && direction_y == 0)
        {
            WaitforPushTimer();
            SetBlockVelocityX(block, -1);
        }
        else if (direction_y == 1 && direction_x == 0)
        {
            WaitforPushTimer();
            SetBlockVelocityY(block, -1);
        }
        else if (direction_y == -1 && direction_x == 0)
        {
            WaitforPushTimer();
            SetBlockVelocityY(block, 1);
        }
    }
    else
    {
        if (direction_x == 1 && direction_y == 0)
        {
            player->x -= 1;
        }
        else if (direction_x == -1 && direction_y == 0)
        {
            player->x += 1;
        }
        else if (direction_y == 1 && direction_x == 0)
        {
            player->y += 1;
        }
        else if (direction_y == -1 && direction_x == 0)
        {
            player->y -= 1;
        }
    }

    if ((direction_y == -1 && direction_x == 1))
    {
        player->x -= 1;
        player->y -= 1;
    }
    else if ((direction_y == 1 && direction_x == -1))
    {
        player->x += 1;
        player->y += 1;
    }
    else if ((direction_y == -1 && direction_x == -1))
    {
        player->x += 1;
        player->y -= 1;
    }
    else if ((direction_y == 1 && direction_x == 1))
    {
        player->x -= 1;
        player->y += 1;
    }

    return moves--;
}
