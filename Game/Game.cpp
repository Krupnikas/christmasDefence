#include <Game/Game.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>

CGame::CGame(R *r, CScene *scene, MainView *view) : r(r), scene(scene), view(view)
{
    cannons.resize(CellNumX);
    for (int i = 0; i < CellNumX; ++i)
        cannons[i].resize(CellNumY);
    gameTimer = new QTimer(this);
    gameTimer->start(16);
}

CGame::~CGame()
{
    
}

void CGame::scaleObjects(qreal scaleFactor)
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i]->scaleItem(scaleFactor);
        bullets[i]->draw();
    }
    
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->scaleItem(scaleFactor);
                cannons[i][j]->draw();
            }
}

void CGame::onTimer()
{
    size_t lastBulletInd = 0;
    for (size_t i = 0; i < bullets.size(); ++i)
        if (bullets[i]->move())
        {
            bullets[i]->draw();
            if (lastBulletInd < i)
                bullets[lastBulletInd++] = bullets[i];
            else
                lastBulletInd++;
        }
    if (lastBulletInd < bullets.size())
        bullets.resize(lastBulletInd);
/*    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->draw();*/
}


