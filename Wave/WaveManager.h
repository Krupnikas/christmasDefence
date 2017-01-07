#pragma once

#include <Wave/Wave.h>
#include <QObject>

class CGame;

class CWaveManager : public QObject
{
    Q_OBJECT
public:
    CWaveManager();
    void initialize(CGame *game, int level);

    void setCurWave(int newCurWave);
    void onTimer();
    QString getWaveInfo();
    
    int getNumberOfWaves();

private:
    CGame *game;
    std::vector<CWave> waves;
    
    bool waveGoing;
    int curWave;
    int counter;

signals:

    void curWaveChanged(int newCurWave);

};
