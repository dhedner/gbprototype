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
    UINT8 current_tile;
    UINT8 life;
    UINT8 max_life;
    UINT8 movement_speed;

} PLAYER_DATA;

// Number of tiles for the animation, followed by the tile ids
const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 0, 1};

void UpdateHudLife(Sprite* spr)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;

    for (UINT8 i = 0; i < player->max_life; ++i)
    {
        UPDATE_HUD_TILE(16 + i, 0, i < player->life ? 1 : 2);
    }
}

UINT8 GetPlayerTilePosition(Sprite* spr)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;
    return player->current_tile;
}

UINT8 GetPlayerLife(Sprite* spr)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;
    return player->life;
}

INT8 GetPlayerMovementDirectionX(Sprite* spr)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;
    if (KEY_PRESSED(J_RIGHT))
    {
        return 1;
    }
    else if (KEY_PRESSED(J_LEFT))
    {
        return -1;
    }
    
    return 0;
}

INT8 GetPlayerMovementDirectionY(Sprite* spr)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;
    if (KEY_PRESSED(J_UP))
    {
        return 1;
    }
    else if (KEY_PRESSED(J_DOWN))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void SetPlayerLife(Sprite* spr, UINT8 amount)
{
    PLAYER_DATA* player = (PLAYER_DATA*)spr->custom_data;
    player->life = amount;
}

void START()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    player->movement_speed = 1;
    player->current_tile = 0;
    player->life = 3;
    player->max_life = 3;
}

void UPDATE()
{
    PLAYER_DATA* player = (PLAYER_DATA*)THIS->custom_data;

    UINT8 i;
    Sprite* spr;

    if (KEY_PRESSED(J_UP))
    {
        player->current_tile = TranslateSprite(THIS, 0, -player->movement_speed);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_DOWN))
    {
        player->current_tile = TranslateSprite(THIS, 0, player->movement_speed);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_LEFT))
    {
        player->current_tile = TranslateSprite(THIS, -player->movement_speed, 0);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_RIGHT))
    {
        player->current_tile = TranslateSprite(THIS, player->movement_speed, 0);
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
                UpdateHudLife(THIS);

                if (!player->life)
                {
                    SetState(StateGame);
                }
            }
        }
    }
}

void DESTROY()
{
}
