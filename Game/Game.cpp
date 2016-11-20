#include <Game/Game.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Helper.h>

CGame::CGame(R *r, CScene *scene, MainView *view) : r(r), scene(scene), view(view)
{
    cannons.resize(CellNumX);
    distances.resize(CellNumX);
    for (int i = 0; i < CellNumX; ++i)
    {
        cannons[i].resize(CellNumY);
        distances[i].resize(CellNumY);
    }
    gameTimer = new QTimer(this);
    gameTimer->start(16);
}

CGame::~CGame()
{
    
}

void CGame::updatePath()
{
    helper::calcDistances(cannons, distances);
    
    if (DrawText)
        for (int i = 0; i < CellNumX; ++i)
            for (int j = 0; j < CellNumY; ++j)
            {
                std::string text(std::to_string(distances[i][j]));
                scene->drawAndPosition(OffsetX + i * CellSize, OffsetY + j * CellSize, QString(text.c_str()), 0.5);
            }
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

QPoint CGame::findNearestCell(QPointF from)
{
    double minDist = CellSize;
    double manhattanLength;
    QPoint nearestCell;
    for (int i = 0; i < CellNumX; ++i)
    {
        for (int j = 0; j < CellNumY; ++j)
        {
            int x = OffsetX + i * CellSize + CellSize/ 2.0;
            int y = OffsetY + j * CellSize + CellSize/ 2.0;
            QPointF checkingCellCenter(x,y);
            checkingCellCenter -= from;
            manhattanLength = abs(checkingCellCenter.x()) + abs(checkingCellCenter.y());
            if (manhattanLength < minDist){
                    minDist = manhattanLength;
                    nearestCell.setX(i);
                    nearestCell.setY(j);
            }
        }
    }
    return nearestCell;
}

bool CGame::addCannon(QPoint cell)
{
    return addCannon(cell.x(), cell.y());
}

bool CGame::addCannon(int x, int y)
{
    if (x < 0 || x > CellNumX ||
        y < 0 || y > CellNumY)
            return false;
    cannons[x][y]
            = std::make_shared<CFastCannon>(this, x, y, 100, 30, 100);
    CFastCannon *can = reinterpret_cast<CFastCannon*>(cannons[x][y].get());
    connect(gameTimer, SIGNAL(timeout()), can, SLOT(onTimer()));
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


