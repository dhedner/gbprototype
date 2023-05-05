#include "Banks/SetAutoBank.h"
#include "ZGBMain.h" // For access to all sprite types

#include "SpriteManager.h"

typedef struct CUSTOM_DATA
{
    INT8 velocity_y;
} CUSTOM_DATA;

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->velocity_y = 1;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if (TranslateSprite(THIS, 0, data->velocity_y << delta_time))
    {
        data->velocity_y = -data->velocity_y;
    }
}

void DESTROY()
{
}