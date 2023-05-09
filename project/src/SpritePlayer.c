#include "Banks/SetAutoBank.h"
#include "ZGBMain.h" // For access to all sprite types
#include "types.h"

#include "Keys.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "Print.h"

// Number of tiles for the animation, followed by the tile ids
const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 0, 1};

UINT8 life;

void UpdateHudLife()
{
    for (UINT8 i = 0; i < 3; ++i)
    {
        UPDATE_HUD_TILE(16 + i, 0, i < life ? 1 : 2);
    }
}

void START()
{
    life = 3;
}

void UPDATE()
{
    UINT8 i;
    Sprite* spr;

    if (KEY_PRESSED(J_UP))
    {
        TranslateSprite(THIS, 0, -1 << delta_time);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_DOWN))
    {
        TranslateSprite(THIS, 0, 1 << delta_time);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_LEFT))
    {
        TranslateSprite(THIS, -1, 0 << delta_time);
        SetSpriteAnim(THIS, anim_walk, 15);
    }
    if (KEY_PRESSED(J_RIGHT))
    {
        TranslateSprite(THIS, 1, 0 << delta_time);
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
                life--;
                UpdateHudLife();
                if (!life)
                {
                    SetState(StateGame);
                }
            }
        }
    }

    DPRINT_POS(0, 0);
    DPrintf("Life: %d ", life);

    DPRINT_POS(0, 1);
    DPrintf("x:%d y:%d ", THIS->x, THIS->y);
}

void DESTROY()
{
}