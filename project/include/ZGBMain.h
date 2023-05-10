#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES                                                                                     \
    _STATE(StateGame)                                                                              \
    _STATE(StateGame2)                                                                             \
    STATE_DEF_END

#define SPRITES                                                                                    \
    _SPRITE_DMG(SpritePlayer, player)                                                              \
    _SPRITE_DMG(SpriteEnemy, enemy)                                                                \
    SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif