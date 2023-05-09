#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"

#include "Print.h"
#include "Scroll.h"
#include "SpriteManager.h"

IMPORT_TILES(font);
IMPORT_MAP(hud);
IMPORT_MAP(map2);

UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 0};

Sprite* player_sprite = NULL;

void START()
{
    player_sprite = SpriteManagerAdd(SpritePlayer, 72, 112);

    InitScroll(BANK(map2), &map2, collision_tiles, 0);
    INIT_HUD(hud);
    INIT_CONSOLE(font, 3);
}

void UPDATE()
{
    UINT8 result = TranslateSprite(player_sprite, 0, 1 << delta_time);

    if (result == collision_tiles[1] || result == collision_tiles[2] ||
        result == collision_tiles[3] || result == collision_tiles[4])
    {
        SetState(StateGame);
    }

    DPRINT_POS(0, 0);
    DPrintf("Tile: %d ", result);
}
