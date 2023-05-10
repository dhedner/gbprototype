#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"

#include "SpritePlayer.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"

IMPORT_TILES(font);
IMPORT_MAP(hud);
IMPORT_MAP(map2);

UINT8 collision_tiles2[] = {1, 2, 3, 0};

Sprite* player_sprite = NULL;
//Sprite* block_sprite = NULL;

void START()
{
    player_sprite = SpriteManagerAdd(SpritePlayer, 72, 112);

    InitScroll(BANK(map2), &map2, collision_tiles2, 0);
    INIT_HUD(hud);
    INIT_CONSOLE(font, 3);
}

void UPDATE()
{
    UINT8 result = GetPlayerTilePosition();

    if (result == collision_tiles2[1] || result == collision_tiles2[2])
    {
        SetState(StateGame);
    }

    DPRINT_POS(0, 0);
    DPrintf("Tile: %d ", result);
}
