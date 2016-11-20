#pragma once

//all sizes are in pixels in local coordinate system 

const int LocalWidth = 1600;
const int LocalHeight = 900;

const int MenuButtonOffset = 2;

const int OffsetY = 100;

const int CellNumY = 7; //always odd
const int CellSize = (LocalHeight - 2 * OffsetY) / CellNumY;
const int CellNumX = LocalWidth / CellSize - MenuButtonOffset;

const int OffsetX = (LocalWidth - CellNumX * CellSize) / 2;

const int BulletSizeX = 50;
const int BulletSizeY = 50;

const qreal FastBulletStep = CellSize / 30.0;

const bool ExitLeft = true;
const int ExitX = ExitLeft ? 0 : CellNumX - 1;
const int ExitY = CellNumY / 2;
const int EntranceX = ExitLeft ? CellNumX - 1 : 0;
const int EntranceY = CellNumY / 2;

const bool DrawText = true;
