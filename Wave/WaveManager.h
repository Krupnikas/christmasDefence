#pragma once

#include <Game/Resource.h>

class CGame;

class CWaveManager
{
public:
    CWaveManager(CGame *game);
    onTimer();
    
private:
    CGame *game;
    bool waveComes;
    int counter;
};
