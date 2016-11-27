#pragma once

#include <QSize>

//all sizes are in pixels in local coordinate system 

const int LocalWidth = 1600;
const int LocalHeight = 900;

const int MenuButtonOffset = 1;
const int CannonSelectionOffsetX = 50;
const int CannonSelectionOffsetY = 50;

const int OffsetY = 15;

const int CellNumY = 7; //always odd
const int CellSize = (LocalHeight - 2 * OffsetY) / CellNumY;
const int CellNumX = LocalWidth / CellSize - MenuButtonOffset;

const int OffsetX = (LocalWidth - CellNumX * CellSize) / 2;

const int BulletSizeX = CellSize / 3.0;
const int BulletSizeY = CellSize / 3.0;

const qreal FastCannonRotation = 5; // in angles
const qreal FastCannonRadius = 500;
const qreal FastCannonInterval = 50;

// in local points
const qreal FastBulletStep = CellSize / 15.0;

// in local points
const qreal FastEnemyStep = CellSize / 20.0;
const QSizeF FastEnemySize(CellSize / 2.0, CellSize / 2.0);

const bool ExitLeft = true;
const int ExitX = ExitLeft ? 0 : CellNumX - 1;
const int ExitY = CellNumY / 2;
const int EntranceX = ExitLeft ? CellNumX - 1 : 0;
const int EntranceY = CellNumY / 2;

#define SHOW_FPS
