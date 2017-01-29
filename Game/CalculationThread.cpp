#include <Game/CalculationThread.h>
#include <Game/Game.h>
#include <Bullet/IBullet.h>
#include <Cannon/ICannon.h>
#include <Enemy/IEnemy.h>
#include <Game/WaveManager.h>

CCalculationThread::CCalculationThread(CGame* game):
    game(game)
{
}

void CCalculationThread::run()
{
    game->waveManager.onTimer();

    size_t lastBulletInd = 0;
    for (size_t i = 0; i < game->bullets.size(); ++i)
        if (game->bullets[i]->move() && !game->bullets[i]->reachedEnemy())
        {
            if (lastBulletInd < i)
                game->bullets[lastBulletInd++] = game->bullets[i];
            else
                lastBulletInd++;
        }
        else
            game->bullets[i]->remove();
    if (lastBulletInd < game->bullets.size())
        game->bullets.resize(lastBulletInd);

    static QElapsedTimer timer;
    timer.start();
    size_t lastEnemyInd = 0;
    for (size_t i = 0; i < game->enemies.size(); ++i)
        if (!game->enemies[i]->isDead() && game->enemies[i]->move())
        {
            if (lastEnemyInd < i)
                game->enemies[lastEnemyInd++] = game->enemies[i];
            else
                lastEnemyInd++;
        }
        else
            game->enemies[i]->remove();
    if (lastEnemyInd < game->enemies.size())
        game->enemies.resize(lastEnemyInd);
    
    qint64 elapsed = timer.nsecsElapsed();
    //if (elapsed > 1e6)
        qDebug() << "enemies counting " << elapsed / 1e6f;
    
    
    
    game->cannonsMutex.lock();
    timer.restart();
    
    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
            if (game->cannons[i][j])
            {
                game->cannons[i][j]->count();
                game->cannons[i][j]->rotate();
            }
    
    elapsed = timer.nsecsElapsed();
    //if (elapsed > 5e6)
        qDebug() << "cannons counting " << elapsed / 1e6f;
    game->cannonsMutex.unlock();
    
    static QTime time;
    static int frameCnt=0;
    static double timeElapsed=0;
    // tps counting...
    frameCnt++;
    timeElapsed += time.elapsed();
    time.restart();
    if (timeElapsed >= 500)
    {
       game->tps = frameCnt * 1000.0 / timeElapsed;
       timeElapsed = 0;
       frameCnt = 0;
    }  
}
