#include <Game/Game.h>
#include <Bullet/FastBullet.h>
#include <Enemy/FastEnemy.h>
#include <Cannon/FastCannon.h>
#include <Game/Helper.h>
#include <InfoBlock/CannonSelection.h>

CGame::CGame(R *r, CScene *scene, QWidget *view) : r(r), scene(scene), view(view), block(nullptr)
{
    cannons.resize(CellNumX);
    distances.resize(CellNumX);
    for (int i = 0; i < CellNumX; ++i)
    {
        cannons[i].resize(CellNumY);
        distances[i].resize(CellNumY);
    }
    helper::calcDistances(cannons, distances);
    
    gameTimer = new QTimer(this);
    gameTimer->start(16);
    gameTimer2 = new QTimer(this);
    gameTimer2->start(16);
}

CGame::~CGame()
{
    
}

bool CGame::addCannon(std::shared_ptr<ICannon> cannon)
{
    int x = cannon->getX();
    int y = cannon->getY();
    
    if (x < 0 || x > CellNumX ||
        y < 0 || y > CellNumY/* ||
        !enemies.empty()*/)
        return false;
    
    cannons[x][y] = cannon;
    if (!helper::calcDistances(cannons, distances))
    {
        cannons[x][y] = nullptr;
        return false;
    }
    
    updateDistances();
    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->updateDistances();
    scene->updateDistances(distances);
    return true;
}

bool CGame::addEnemy(std::shared_ptr<IEnemy> enemy)
{
    enemies.push_back(enemy);
    enemy->draw();
    enemy->show();
    return true;
}

void CGame::updateDistances()
{
    helper::calcDistances(cannons, distances);
}

void CGame::scaleObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i]->scaleItem();
        bullets[i]->draw();
    }
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->scaleItem();
        enemies[i]->draw();
    }
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->scaleItem();
                cannons[i][j]->draw();
            }
    
    if (block)
    {
        block->scaleItem();
        block->draw();
    }
    if (selectedCellItem)
    {
        scene->removeItem(selectedCellItem);
        selectedCellItem = nullptr;
        selectCell(selectedCell.x(), selectedCell.y());
    }
    
    scene->updateDistances(distances);
}

void CGame::hideObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->hide();
    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->hide();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->hide();
    if (block)
        block->hide();
    if (selectedCellItem)
        selectedCellItem->hide();
}

void CGame::showObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->show();
    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->show();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->show();
    if (block)
        block->show();
    if (selectedCellItem)
        selectedCellItem->show();    
}

void CGame::selectCell(QPoint pos)
{
    selectCell(pos.x(), pos.y());
}

void CGame::selectCell(int i, int j)
{
    selectedCell = QPoint(i, j);

    int x = OffsetX + i * CellSize;
    int y = OffsetY + j * CellSize;
    QSizeF size(CellSize, CellSize);

    if (!selectedCellItem)
        selectedCellItem = scene->addPixmap(size, &(r->cellSelected));
    
    scene->positionItem(QPointF(x, y), size, 0, 0.5, selectedCellItem);
}

void CGame::deselectCell()
{
    selectedCellItem->hide();
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
        y < 0 || y > CellNumY ||
        !enemies.empty())
            return false;
    
    cannons[x][y] = std::make_shared<CFastCannon>(this, x, y, 100, 30, 100);
    return true;
}

void CGame::onTimer()
{
    size_t lastBulletInd = 0;
    for (size_t i = 0; i < bullets.size(); ++i)
        if (bullets[i]->move())
        {
            if (lastBulletInd < i)
                bullets[lastBulletInd++] = bullets[i];
            else
                lastBulletInd++;
        }
    if (lastBulletInd < bullets.size())
        bullets.resize(lastBulletInd);
    
    size_t lastEnemyInd = 0;
    for (size_t i = 0; i < enemies.size(); ++i)
        if (enemies[i]->move())
        {
            if (lastEnemyInd < i)
                enemies[lastEnemyInd++] = enemies[i];
            else
                lastEnemyInd++;
        }
    if (lastEnemyInd < enemies.size())
        enemies.resize(lastEnemyInd);
    
    static QTime time;
    static int frameCnt=0;
    static double timeElapsed=0;
    // fps counting...
    frameCnt++;
    timeElapsed += time.elapsed();
    time.restart();
    if (timeElapsed >= 500)
    {
       tps = frameCnt * 1000.0 / timeElapsed;
       timeElapsed = 0;
       frameCnt = 0;
    }
}

void CGame::onTimer2()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();
    
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
    
    static QTime time;
    static int frameCnt=0;
    static double timeElapsed=0;
    // fps counting...
    frameCnt++;
    timeElapsed += time.elapsed();
    time.restart();
    if (timeElapsed >= 500)
    {
       fps = frameCnt * 1000.0 / timeElapsed;
       timeElapsed = 0;
       frameCnt = 0;
    }
    scene->updateFPS(fps, tps);
}


