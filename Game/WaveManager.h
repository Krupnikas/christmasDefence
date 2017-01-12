#pragma once

#include <Game/Wave.h>

class CGame;

class CWaveManager : public QObject
{
    Q_OBJECT
    
//public methods:
public:
    CWaveManager(CGame *game);
    void initialize();

    void setCurWave(int newCurWave);
    void onTimer();
    QString getWaveInfo();
    
    int getNumberOfWaves();
    
    
//publics fields
public:
    std::vector<CWave> waves;

    
//private fields
private:
    CGame *game;
    
    
    bool waveGoing;
    int curWave;
    int counter;

//signals
signals:
    void curWaveChanged(int newCurWave);

};
