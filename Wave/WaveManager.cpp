#include <Wave/WaveManager.h>
#include <Wave/Wave.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CWaveManager::CWaveManager():
    waveGoing(false),
    curWave(0),
    counter(0)
{}

void CWaveManager::initialize(CGame *game)
{
    this->game = game;
    helper::readWaves(game->r->waves, waves, game);
}

void CWaveManager::onTimer()
{
    if (curWave < waves.size())
    {
        counter++;
        qreal curTime = helper::ticksToTime(counter);
        if (!waveGoing)
        {
            if (curTime >= waves[curWave].timeBeforeStart)
            {
                waveGoing = true;
                counter = 0;
            }
        } 
        else
        {
            if (curTime >= waves[curWave].enemyIncomeInterval)
            {
                if (!waves[curWave].enemies.empty())
                {
                    game->addEnemy(waves[curWave].enemies.front());
                    waves[curWave].enemies.pop();
                    counter = 0;
                }
                else if (game->enemies.empty())
                {
                    waveGoing = false; 
                    counter = 0;
                }
                
            }
        }
    }
}
