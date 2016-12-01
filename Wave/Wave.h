#pragma once

#include <Game/Resource.h>

class IEnemy;

struct CWave
{
    CWave();
    std::vector<std::shared_ptr<IEnemy>> enemies;
    int timeBeforeStart;
    int enemyIncomeInterval;    
};
