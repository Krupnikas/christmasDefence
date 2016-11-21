#include <Game/Game.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Helper.h>

CGame::CGame(R *r, CScene *scene, QWidget *view) : r(r), scene(scene), view(view)
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

bool CGame::addCannon(std::shared_ptr<ICannon> cannon)
{
    int x = cannon->getX();
    int y = cannon->getY();
    cannons[x][y] = cannon;
    if (!helper::calcDistances(cannons, distances))
    {
        cannons[x][y] = nullptr;
        return false;
    }
    
    scene->updateDistances(distances);
    return true;
}

void CGame::scaleObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i]->scaleItem();
        bullets[i]->draw();
    }
    
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->scaleItem();
                cannons[i][j]->draw();
            }
    scene->updateDistances(distances);
}

void CGame::selectCell(QPoint pos)
{
    selectCell(pos.x(), pos.y());
}

void CGame::selectCell(int i, int j)
{
    deselectCell();
    selectedCell = QPoint(i, j);

    int x = OffsetX + i * CellSize;
    int y = OffsetY + j * CellSize;

    scene->selectedCellItem = scene->drawAndPosition(x, y, CellSize, CellSize, &(r->cellSelected), 0, 0.5);
}

void CGame::deselectCell()
{
    if (selectedCell == QPoint(-1,-1)) return;
    scene->removeItem(scene->selectedCellItem);
    selectedCell = QPoint(-1, -1);
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
    
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                QPointF center = cannons[i][j]->getCenter();
                QPoint p = view->mapFromGlobal(QCursor::pos());
                int x1 = scene->toGlobalX(center.x());
                int y1 = scene->toGlobalY(center.y());
                cannons[i][j]->setAngle(helper::calcAngle(x1, y1, p.x(), p.y()));
                cannons[i][j]->draw();
            }
}


