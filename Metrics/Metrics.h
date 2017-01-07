#pragma once

#include <QSize>

const bool CloseButtonInInfoBlocksEnabled = true;

//all sizes are in pixels in local coordinate system 

const int LocalWidth = 1600;
const int LocalHeight = 900;

const int MenuButtonOffset = 1;

const int OffsetY = 15;

const int CellNumY = 7; //always odd
const int CellSize = (LocalHeight - 2 * OffsetY) / CellNumY;
const int CellNumX = LocalWidth / CellSize - MenuButtonOffset;

const int CannonSelectionButtonSize = round(1.0 * CellSize);
const int CannonSelectionRadius = 1.1 * CellSize;
const int CannonUpgradeButtonSize = round(1.0 * CellSize);
const int CannonUpgradeRadius = 1.1 * CellSize;

const int OffsetX = (LocalWidth - CellNumX * CellSize) / 2;

const bool ExitLeft = false;
const int ExitX = ExitLeft ? 0 : CellNumX - 1;
const int ExitY = CellNumY / 2;
const int EntranceX = ExitLeft ? CellNumX - 1 : 0;
const int EntranceY = CellNumY / 2;

const int TimerInterval = 16;

const int GameMenuButtonNum = 4;
const int LevelNum = 20;

const int UserCash = 20;
const int UserHp = 30;

#include <Metrics/ZOrderMetrics.h>
#include <Metrics/CannonMetrics.h>
#include <Metrics/EnemyMetrics.h>
#include <Metrics/BulletMetrics.h>

#define SHOW_FPS
