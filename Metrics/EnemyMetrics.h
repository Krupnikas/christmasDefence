#pragma once

//Fast enemy
// in local points

const qreal FastEnemyStep = CellSize / 500.0;

const QSizeF FastEnemyTextureSize(CellSize * 0.6, CellSize * 0.6);
const QSizeF FastEnemySize(FastEnemyTextureSize * 0.4);

const int EnemyHpFactor = 80;
const int EnemyCostFactor = 50;

const QSizeF HpSize(CellSize * 0.7, CellSize * 0.05);
