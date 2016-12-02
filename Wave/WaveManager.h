#pragma once

#include <Wave/Wave.h>

class CGame;

class CWaveManager
{
public:
    CWaveManager();
    void initialize(CGame *game);
    void onTimer();
    QString getWaveInfo();
    
private:
    CGame *game;
    std::vector<CWave> waves;
    
    bool waveGoing;
    int curWave;
    int counter;
};
