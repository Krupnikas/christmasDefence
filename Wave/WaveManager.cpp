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
    std::string info;
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
                info = std::string("Left: " + std::to_string(wave.totalEnemyNum));
            }
            else
                info = std::to_string(
                            static_cast<int>(wave.timeBeforeStart - curTime)) + "   ";
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
            
            int inside = 0;
            for (auto enemy: game->enemies)
                if (game->scene->insideGameRect(enemy->getCenter()))
                    ++inside;
            info = std::string("Left: " + std::to_string(wave.totalEnemyNum - inside));
        }
        
    }
    else
    {
        info = std::string("congrats!");    
    }
    
    game->scene->updateWaveInfo(QString(info.c_str()));
}

QString CWaveManager::getWaveInfo()
{
    return QString("Keep your head up and your ass down");
}
