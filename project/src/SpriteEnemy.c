#include "Banks/SetAutoBank.h"
#include "ZGBMain.h" // For access to all sprite types

#include "SpriteManager.h"

typedef struct ENEMY_DATA
{
    INT8 velocity_y;
} ENEMY_DATA;

void SetEnemyVelocityY(Sprite* sprite, INT8 velocity_y)
{
	ENEMY_DATA* enemy = (ENEMY_DATA*)sprite->custom_data;
	enemy->velocity_y = velocity_y;
}

void START()
{
    SetEnemyVelocityY(THIS, 1);
}

void UPDATE()
{
    ENEMY_DATA* enemy = (ENEMY_DATA*)THIS->custom_data;

    if (TranslateSprite(THIS, 0, enemy->velocity_y << delta_time))
    {
        enemy->velocity_y = -enemy->velocity_y;
    }
}

void DESTROY()
{
}
