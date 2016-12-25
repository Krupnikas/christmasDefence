#include <Game/Game.h>
#include <Bullet/FastBullet.h>
#include <Enemy/FastEnemy.h>
#include <Cannon/FastCannon.h>
#include <Game/Helper.h>
#include <InfoBlock/CannonSelection.h>
#include <InfoBlock/CannonUpgrade.h>
#include <Wave/WaveManager.h>


CGame::CGame(R *r, CScene *scene, QWidget *view):
    r(r),
    scene(scene),
    view(view)
{
    cannons.resize(CellNumX);
    distances.resize(CellNumX);
    for (int i = 0; i < CellNumX; ++i)
    {
        cannons[i].resize(CellNumY);
        distances[i].resize(CellNumY);
    }
    helper::updateDistances(cannons, distances);

    pressedButton = eBTnone;

    positionTimer = new QTimer(this);
    drawTimer = new QTimer(this);

    positionTimer->start(TimerInterval);
    drawTimer->start(TimerInterval);
}

CGame::~CGame()
{

}

void CGame::startLevel(int level)
{
    waveManager.initialize(this, level);
    positionTimer->start(TimerInterval);
    drawTimer->start(TimerInterval);
}

void CGame::end()
{
    positionTimer->stop();
    drawTimer->stop();
}

void CGame::resize()
{
    scene->updateWindowBackground();
    scene->updateGameBackground();
    scaleObjects();
}

bool CGame::isGameCell(QPoint cell)
{
    return cell.x() >= 0 && cell.x() < CellNumX && cell.y() >= 0 && cell.y() < CellNumY;
}

bool CGame::addCannon(std::shared_ptr<ICannon> cannon)
{
    QPoint cell = cannon->getGameCell();
    int x = cell.x();
    int y = cell.y();

    int cost = cannon->getCurCost();

    if (x < 0 || x > CellNumX   ||
        y < 0 || y > CellNumY   ||
        !helper::okToAdd(x, y, distances, enemies) ||
        cost > user.getCash())
        return false;

    user.decreaseCash(cost);

    cannonAddMutex.lock();
    cannons[x][y] = cannon;
    helper::updateDistances(cannons, distances);
    cannonAddMutex.unlock();
    cannon->draw();
    cannon->show();
    return true;
}

bool CGame::addEnemy(int enemyType, int enemyTexture, int enemyPower)
{
    std::shared_ptr<IEnemy> enemy;
    switch (enemyType)
    {
    case 1:
        enemy = std::make_shared<CFastEnemy>(this, enemyTexture, enemyPower);
        break;
    default:
        qDebug() << "Helper: readWaves: incorrect enemyType";
        enemy = std::make_shared<CFastEnemy>(this, enemyTexture, enemyPower);
    }

    enemies.push_back(enemy);
    enemy->draw();
    enemy->show();
    return true;
}

QPointF CGame::cellLeftTop(QPoint cell)
{
    return QPointF(OffsetX + cell.x() * CellSize, OffsetY + cell.y() * CellSize);
}

QPointF CGame::cellCenter(QPoint cell)
{
    QPointF leftTop(cellLeftTop(cell));
    return QPointF(leftTop.x() + CellSize / 2.0, leftTop.y() + CellSize / 2.0);
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
}

void CGame::selectCell(QPoint pos)
{
    if (!isGameCell(pos))
    {
        qDebug() << "CGame: selecteCell: cell is outside the field";
        return;
    }
    if (selectedCell != UnselCell)
    {
        deselectCell();
        return;
    }

    if (selectedCell == pos)
        return;

    int selX = pos.x();
    int selY = pos.y();
    if (cannons[selX][selY])
        if(cannons[selX][selY]->isRadiusVisible())
        {
            cannons[selX][selY]->hideRadius();
        } else {
            cannons[selX][selY]->showRadius();
        }
    else
    {
        cannonSelectionInfoBlock->updatePosition(pos);
        cannonSelectionInfoBlock->draw();
        cannonSelectionInfoBlock->show();
        int x = OffsetX + selX * CellSize;
        int y = OffsetY + selY * CellSize;
        QSizeF size(CellSize, CellSize);
        if (!selectedCellItem)
            selectedCellItem = scene->addPixmap(size, &(r->cellSelected));

        scene->positionItem(QPointF(x, y), size, 0, 0.5, selectedCellItem);
        selectedCellItem->setFlag(QGraphicsItem::ItemHasNoContents, false);
        selectedCellItem->show();
    }
    selectedCell = pos;
}

void CGame::deselectCell()
{
    int selX = selectedCell.x();
    int selY = selectedCell.y();
    if (cannons[selX][selY])
        cannons[selX][selY]->hideRadius();
    if (cannonSelectionInfoBlock)
        cannonSelectionInfoBlock->hide();
    if (selectedCellItem)
    {
        selectedCellItem->hide();
        selectedCellItem->setFlag(QGraphicsItem::ItemHasNoContents, true);
    }
    selectedCell = QPoint(-1, -1);
}

QPoint CGame::findNearestCell(QPointF from)
{
    QPoint nearestCell(-1, -1);
    nearestCell.setX((from.x() - OffsetX) / CellSize);
    nearestCell.setY((from.y() - OffsetY) / CellSize);
    return nearestCell;
}

void CGame::onPositionTimer()
{
    waveManager.onTimer();

    size_t lastBulletInd = 0;
    for (size_t i = 0; i < bullets.size(); ++i)
        if (bullets[i]->move() && !bullets[i]->reachedEnemy())
        {
            if (lastBulletInd < i)
                bullets[lastBulletInd++] = bullets[i];
            else
                lastBulletInd++;
        }
    for (size_t i = lastBulletInd; i < bullets.size(); ++i)
        bullets[i]->remove();
    if (lastBulletInd < bullets.size())
        bullets.resize(lastBulletInd);

    size_t lastEnemyInd = 0;
    for (size_t i = 0; i < enemies.size(); ++i)
        if (!enemies[i]->isDead() && enemies[i]->move())
        {
            if (lastEnemyInd < i)
                enemies[lastEnemyInd++] = enemies[i];
            else
                lastEnemyInd++;
        }
    for (size_t i = lastEnemyInd; i < enemies.size(); ++i)
        enemies[i]->remove();
    if (lastEnemyInd < enemies.size())
        enemies.resize(lastEnemyInd);
}

void CGame::onDrawTimer()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();

    for (auto enemy: enemies)
        enemy->draw();

    cannonAddMutex.lock();

        for (int i = 0; i < CellNumX; ++i)
            for (int j = 0; j < CellNumY; ++j)
                if (cannons[i][j])
                {
                    cannons[i][j]->count();
                    cannons[i][j]->rotate();
                }

    cannonAddMutex.unlock();

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
    scene->updateFPS(fps);
    scene->updateUserInfo(user.getCash(), user.getHp());
}

void CGame::onMousePressed(QMouseEvent *pressEvent)
{
    emit mousePressed(pressEvent);
}


void CGame::scaleObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i]->scaleItem();
        bullets[i]->draw();
        bullets[i]->show();
    }
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->scaleItem();
        enemies[i]->draw();
        enemies[i]->show();
    }
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->scaleItem();
                cannons[i][j]->draw();
                cannons[i][j]->show();
            }

    if (block)
    {
        block->scaleItem();
        block->closeButton.scaleItem();

        for (int i = 0; i < TypesOfCannon; i++)
        {
            block->cannonButton[i].scaleItem();
        }

        block->updateButtonsPositions();
        block->draw();
    }

    if (selectedCellItem)
    {
        scene->removeItem(selectedCellItem);
        selectedCellItem = nullptr;
        selectCell(selectedCell);
    }
}
