#include <Game/WaveManager.h>
#include <Game/Wave.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>
#include <InfoBlock/WaveInfoBlock.h>

CWaveManager::CWaveManager(CGame *game):
    game(game),
    waveGoing(false),
    curWave(0),
    counter(0)
{}

void CWaveManager::initialize()
{
    waveGoing = false;
    counter = 0;
    curWave = 0;
 
    if (static_cast<int>(waves.size()) <= curWave)
        qDebug() << "CWaveManager: initialize: too few waves";
    
    //initialize waveInfoBlock
    game->waveInformationBlock->setTotalWaveNum(waves.size());
    game->waveInformationBlock->onCurWaveChanged(curWave);
    
    if (static_cast<int>(waves.size()) > curWave)
        game->waveInformationBlock->onEnemyNumChanged(waves[curWave].totalEnemyNum);
    else
        game->waveInformationBlock->onEnemyNumChanged(0);
    
}

void CWaveManager::setCurWave(int newCurWave)
{
    curWave = newCurWave;
    game->waveInformationBlock->onCurWaveChanged(curWave);
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
                    //qDebug() << "WaveManager: enemy added!";
                    wave.curEnemyNum++;
                    counter = 0;
                }

                if (game->enemies.empty())
                {
                    waveGoing = false;
                    counter = 0;
                    setCurWave(curWave + 1);
                    game->waveInformationBlock->onEnemyNumChanged(waves[curWave].totalEnemyNum);
                    return;
                }
            }

            int outside = 0;
            for (auto enemy: game->enemies)
                if (!enemy->getWasInsideGame())
                    ++outside;
            game->waveInformationBlock->onEnemyNumChanged(wave.totalEnemyNum - wave.curEnemyNum + outside);
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

int CWaveManager::getNumberOfWaves()
{
    return static_cast<int>(waves.size());
}
