#pragma once

#include <QPoint>

namespace m
{

bool CloseButtonInInfoBlocksEnabled = true;
int TimerInterval = 16;

int OffsetY;
int OffsetX;

int CellNumX;
int CellNumY;
int CellSize;

int CannonSelectionButtonSize;
int CannonSelectionRadius;
int CannonUpgradeButtonSize;
int CannonUpgradeRadius;

QPoint startCell;
QPoint endCell;

}

#include <Metrics/ZOrderMetricsDef.h>
#include <Metrics/CannonMetricsDef.h>
#include <Metrics/EnemyMetricsDef.h>
#include <Metrics/BulletMetricsDef.h>
