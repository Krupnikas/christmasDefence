#pragma once

//Fast enemy
// in local points

const qreal FastEnemyStep = CellSize / 500.0;

const QSizeF FastEnemyTextureSize(CellSize * 0.8, CellSize * 0.8);
const QSizeF FastEnemySize(FastEnemyTextureSize * 1/*0.4*/);

const int EnemyHpFactor = 65;
const int EnemyCostFactor = 500;

const QSizeF HpSize(CellSize * 0.7, CellSize * 0.05);
