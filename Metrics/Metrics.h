#pragma once

#include <QSize>
#include <QPoint>

namespace m
{

//all sizes are in pixels in local coordinate system 

const int LocalWidth = 1600;
const int LocalHeight = 900;

const int GameMenuButtonNum = 4;
const int LevelNum = 20;

const qreal SoundLevel = 0.1;

//const int MenuButtonOffset = 1;
extern bool CloseButtonInInfoBlocksEnabled;
extern int PositionTimerInterval;
extern int DrawTimerInterval;

extern int OffsetY;
extern int OffsetX;

extern int CellNumX;
extern int CellNumY;
extern int CellSize;

extern int CannonSelectionButtonSize;
extern int CannonSelectionRadius;
extern int CannonUpgradeButtonSize;
extern int CannonUpgradeRadius;

extern std::vector<QPoint> startCells;
extern std::vector<QPoint> endCells;

}

#include <Metrics/ZOrderMetrics.h>
#include <Metrics/CannonMetrics.h>
#include <Metrics/EnemyMetrics.h>
#include <Metrics/BulletMetrics.h>

#define SHOW_FPS
