#include "Banks/SetAutoBank.h"
#include "ZGBMain.h" // For access to all sprite types
#include "types.h"

#include "Keys.h"
#include "Print.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "SpritePlayer.h"

typedef struct PLAYER_DATA
{
    INT8 velocity_x;
    INT8 velocity_y;
    UINT8 current_tile;
    UINT8 life;
} PLAYER_DATA;

// Number of tiles for the animation, followed by the tile ids
const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 0, 1};

void UpdateHudLife()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    for (UINT8 i = 0; i < 3; ++i)
    {
        UPDATE_HUD_TILE(16 + i, 0, i < player->life ? 1 : 2);
    }
}

UINT8 GetPlayerTilePosition()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    return player->current_tile;
}

void START()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    player->velocity_x = 1;
    player->velocity_y = 1;
    player->current_tile = 0;
    player->life = 3;
}

void UPDATE()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    UINT8 i;
    Sprite* spr;

    if (KEY_PRESSED(J_UP))
    {
        player->current_tile = TranslateSprite(THIS, 0, -player->velocity_y);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_DOWN))
    {
        player->current_tile = TranslateSprite(THIS, 0, player->velocity_y);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_LEFT))
    {
        player->current_tile = TranslateSprite(THIS, -player->velocity_x, 0);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_RIGHT))
    {
        player->current_tile = TranslateSprite(THIS, player->velocity_x, 0);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (keys == 0)
    {
        SetSpriteAnim(THIS, anim_idle, 15);
    }

    SPRITEMANAGER_ITERATE(i, spr)
    {
        if (spr->type == SpriteEnemy)
        {
            if (CheckCollision(THIS, spr))
            {
                SpriteManagerRemove(i);
                player->life--;
                UpdateHudLife();
                if (!player->life)
                {
                    SetState(StateGame);
                }
            }
        }
    }

    DPRINT_POS(0, 1);
    DPrintf("x:%d y:%d ", THIS->x, THIS->y);
}

void DESTROY()
{
}
