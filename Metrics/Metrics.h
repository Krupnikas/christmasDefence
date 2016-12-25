#pragma once

#include <QSize>
#include <Metrics/ZOrderMetrics.h>



//all sizes are in pixels in local coordinate system 

const int LocalWidth = 1600;
const int LocalHeight = 900;

const int MenuButtonOffset = 1;
const int CannonSelectionOffsetX = 20;
const int CannonSelectionOffsetY = 20;

const int OffsetY = 15;

const int CellNumY = 7; //always odd
const int CellSize = (LocalHeight - 2 * OffsetY) / CellNumY;
const int CellNumX = LocalWidth / CellSize - MenuButtonOffset;

const int CannonSelectionButtonSize = round(1.0 * CellSize);
const int CannonSelectionRadius = 1.1 * CellSize;

const int OffsetX = (LocalWidth - CellNumX * CellSize) / 2;

const bool ExitLeft = true;
const int ExitX = ExitLeft ? 0 : CellNumX - 1;
const int ExitY = CellNumY / 2;
const int EntranceX = ExitLeft ? CellNumX - 1 : 0;
const int EntranceY = CellNumY / 2;

const int TimerInterval = 16;

const int UserCash = 200;
const int UserHp = 300;

#include <Metrics/CannonMetrics.h>
#include <Metrics/EnemyMetrics.h>
#include <Metrics/BulletMetrics.h>

#define SHOW_FPS
