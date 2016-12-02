#pragma once

#include <Game/Resource.h>

class IEnemy;

struct CWave
{
    CWave();
    qreal timeBeforeStart;
    qreal enemyIncomeInterval;
    int enemyType;
    int enemyTexture;
    int enemyPower;
    
    int totalEnemyNum;
    int curEnemyNum;
};
