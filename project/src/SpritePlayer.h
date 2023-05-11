#pragma once

void UpdateHudLife(Sprite* spr);

UINT8 GetPlayerTilePosition(Sprite* spr);
UINT8 GetPlayerLife(Sprite* spr);
INT8 GetPlayerMovementDirectionX(Sprite* spr);
INT8 GetPlayerMovementDirectionY(Sprite* spr);

void SetPlayerLife(Sprite* spr, UINT8 amount);
