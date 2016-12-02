#pragma once

#include <Game/Resource.h>

class IEnemy;

struct CWave
{
    CWave();
    std::queue<std::shared_ptr<IEnemy>> enemies;
    qreal timeBeforeStart;
    qreal enemyIncomeInterval;    
};
