#include <Wave/WaveManager.h>
#include <Wave/Wave.h>
#include <Game/Game.h>
#include <Game/Helper.h>
#include <Enemy/IEnemy.h>

CWaveManager::CWaveManager():
    waveGoing(false),
    curWave(0),
    counter(0)
{}

void CWaveManager::initialize(CGame *game)
{
    this->game = game;
    helper::readWaves(game->r->waves, waves);
}

void CWaveManager::onTimer()
{
    QString info;
    if (curWave < static_cast<int>(waves.size()))
    {
        CWave &wave = waves[curWave];
        counter++;
        qreal curTime = helper::ticksToTime(counter);
        if (!waveGoing)
        {
            if (curTime >= wave.timeBeforeStart)
            {
                waveGoing = true;
                counter = 0;
                info = "Left: " + QString::number(wave.totalEnemyNum);
            }
            else
                info = QString::number(static_cast<int>(wave.timeBeforeStart - curTime)) + "   ";
        } 
        else
        {
            if (curTime >= wave.enemyIncomeInterval)
            {
                if (wave.curEnemyNum < wave.totalEnemyNum)
                {
                    game->addEnemy(wave.enemyType, wave.enemyTexture, wave.enemyPower);                    
                    wave.curEnemyNum++;
                    counter = 0;
                }
                
                if (game->enemies.empty())
                {
                    waveGoing = false; 
                    counter = 0;
                    ++curWave;
                }
                
            }
            
            int outside = 0;
            for (auto enemy: game->enemies)
                if (!game->scene->insideGameRect(enemy->getCenter()))
                    ++outside;
            info = "Left: " + QString::number(wave.totalEnemyNum - wave.curEnemyNum + outside);
        }
        
    }
    else
    {
        info = "congrats!";
    }
    
    game->scene->updateWaveInfo(info);
}

QString CWaveManager::getWaveInfo()
{
    return QString("Keep your head up and your ass down");
}
