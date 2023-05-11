#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"

#include "Print.h"
#include "Scroll.h"
#include "SpriteBlock.h"
#include "SpriteManager.h"
#include "SpritePlayer.h"

IMPORT_TILES(font);
IMPORT_MAP(hud);
IMPORT_MAP(map2);

UINT8 collision_tiles2[] = {1, 2, 3, 0};

Sprite* player_sprite = NULL;
Sprite* block_sprite = NULL;

void START()
{
    player_sprite = SpriteManagerAdd(SpritePlayer, 72, 112);
    block_sprite = SpriteManagerAdd(SpriteBlock, 64, 32);

    SetBlockMoves(block_sprite, 3);

    InitScroll(BANK(map2), &map2, collision_tiles2, 0);
    INIT_HUD(hud);
    INIT_CONSOLE(font, 3);
}

void UPDATE()
{
    UINT8 i;
    Sprite* spr;

    SPRITEMANAGER_ITERATE(i, spr)
    {
        if (spr->type == SpriteBlock)
        {
            if (CheckCollision(player_sprite, spr))
            {
                CheckBlockPush(player_sprite, block_sprite, GetBlockMoves(block_sprite));
            }
        }

        if (spr->type == SpritePlayer)
        {
            DPRINT_POS(0, 0);
            DPrintf("X: %d ", GetPlayerMovementDirectionX(player_sprite));
            DPRINT_POS(0, 1);
            DPrintf("Y: %d ", GetPlayerMovementDirectionY(player_sprite));
            DPRINT_POS(0, 2);
            DPrintf("Moves: %d ", GetBlockMoves(block_sprite));
            // DPrintf("x:%d y:%d ", player_sprite->x, player_sprite->y);

            if (GetPlayerTilePosition(player_sprite) == collision_tiles2[1] ||
                GetPlayerTilePosition(player_sprite) == collision_tiles2[2])
            {
                SetState(StateGame);
            }
        }
    }
}
