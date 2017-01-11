#include <mainview.h>
#include <Helper.h>
#include <Game/Game.h>
#include <Bullet/FastBullet.h>
#include <Enemy/FastEnemy.h>
#include <Cannon/FastCannon.h>
#include <InfoBlock/CannonSelection.h>
#include <InfoBlock/CannonUpgrade.h>
#include <InfoBlock/UserInfo.h>
#include <InfoBlock/WaveInfoBlock.h>
#include <Wave/WaveManager.h>
#include <SceneObject/Button.h>


CGame::CGame(MainView *view, R *r, CScene *scene, QMediaPlaylist *playlist, QMediaPlayer *player):
    view(view),
    r(r),
    scene(scene),
    playlist(playlist),
    player(player),
    user(r),
    selectionStatus(ESelectionStatus::eNone)
{
    cannons.resize(CellNumX);
    distances.resize(CellNumX);
    for (int i = 0; i < CellNumX; ++i)
    {
        cannons[i].resize(CellNumY);
        distances[i].resize(CellNumY);
    }

    pressedButton = EButtonType::eBTnone;

    positionTimer = new QTimer(this);
    drawTimer = new QTimer(this);

    connect(positionTimer, SIGNAL(timeout()), this, SLOT(onPositionTimer()));
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(onDrawTimer()));
}

CGame::~CGame()
{

}

void CGame::create()
{
    background = std::make_shared<CGameBackground>(this);
    cannonSelectionInfoBlock = std::make_shared<CCannonSelection>(this, UnselCell);
    cannonUpgradeInfoBlock = std::make_shared<CCannonUpgrade>(this, UnselCell);
    userInformationBlock = std::make_shared<CUserInfo>(this);
    waveInformationBlock = std::make_shared<CWaveInfoBlock>(this);
        
    menuButton = std::make_shared<CButton>(
                BackgroundZOrder + 0.1,
                QPointF(OffsetX / 2, LocalHeight - CellSize / 2),
                QSizeF(CellSize * 0.7, CellSize * 0.7),
                this, static_cast<int>(EButtonType::eBTgMenu),
                r->game_menu_button
                );
    
    selectionStatus = ESelectionStatus::eNone;
    connect(menuButton.get(), SIGNAL(pressed(int)), this, SLOT(onButtonPressed(int)));
}

void CGame::show()
{
    view->app->removeEventFilter(view);
    
    background->draw();
    background->show();

    userInformationBlock->draw();
    userInformationBlock->show();

    waveInformationBlock->draw();
    waveInformationBlock->show();
    
    menuButton->draw();
    menuButton->show();

    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->show();
    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->show();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->draw();
                cannons[i][j]->show();
            }
    
    switch (selectionStatus)
    {
    case ESelectionStatus::eCannonSelection:
        cannonSelectionInfoBlock->draw();
        cannonSelectionInfoBlock->show();
        break;
    case ESelectionStatus::eCannonUpgrade:
        cannonUpgradeInfoBlock->draw();
        cannonUpgradeInfoBlock->show();
        break;
    default:
        break;
    }
    
    view->gameStatus = EGameStatus::eGame;
}

void CGame::hide()
{
    deselectCell();
    
    background->hide();
    userInformationBlock->hide();
    waveInformationBlock->hide();
    menuButton->hide();

    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->hide();
    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->hide();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->hide();
    
    scene->removeFPS();
    scene->removeWaveInfo();
    
    view->app->installEventFilter(view);
}

void CGame::resize()
{
    scaleObjects();
}

void CGame::close()
{
    deselectCell();
    
    background->remove();
    cannonSelectionInfoBlock->remove();
    cannonUpgradeInfoBlock->remove();
    userInformationBlock->remove();
    waveInformationBlock->remove();
    menuButton->remove();
    
    scene->removeFPS();
    scene->removeWaveInfo();

    endGame();
}

void CGame::mousePressEvent(QMouseEvent *)
{
    if (pressedButton != EButtonType::eBTnone){
        pressedButton = EButtonType::eBTnone;
        return;
    }

    QPointF p = view->mapFromGlobal(QCursor::pos());
    QPoint curSelectedCell = findNearestCell(scene->toLocalPoint(p));

    selectCell(curSelectedCell);
}

void CGame::startGameLevel(int level)
{
    user.setHp(UserHp);
    user.setCash(UserCash);
    
    waveManager.initialize(this, level);
    helper::updateDistances(cannons, distances);

    positionTimer->start(TimerInterval);
    drawTimer->start(TimerInterval);
}

void CGame::endGame()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->remove();
    bullets.clear();

    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->remove();
    enemies.clear();

    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
            {
                cannons[i][j]->remove();
                cannons[i][j] = nullptr;
            }
    
    view->app->installEventFilter(view);
            
    positionTimer->stop();
    drawTimer->stop();
}

bool CGame::isGameCell(QPoint cell)
{
    return cell.x() >= 0 && cell.x() < CellNumX && cell.y() >= 0 && cell.y() < CellNumY;
}

bool CGame::buyCannon(std::shared_ptr<ICannon> cannon)
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

    cannonsMutex.lock();
    cannons[x][y] = cannon;
    helper::updateDistances(cannons, distances);
    cannonsMutex.unlock();
    cannon->draw();
    cannon->show();
    return true;
}

void CGame::sellCannon(std::shared_ptr<ICannon> cannon)
{
    user.increaseCash(cannon->getCurCost() / 4.0 * 3);
    cannon->remove();

    QPoint cell(cannon->getGameCell());

    cannonsMutex.lock();
    cannons[cell.x()][cell.y()] = nullptr;
    helper::updateDistances(cannons, distances);
    cannonsMutex.unlock();
}

void CGame::sellCannon(QPoint cell)
{
    if (!isGameCell(cell))
    {
        qDebug() << "CGame: sellCannon: cell not in game";
        return;
    }

    sellCannon(cannons[cell.x()][cell.y()]);
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

void CGame::selectCell(QPoint pos)
{
    if (!isGameCell(pos))
    {
        qDebug() << "CGame: selecteCell: cell is outside the field";
        return;
    }
    
    if (cannonSelectionInfoBlock->isVisible())
        cannonSelectionInfoBlock->hide();
    if (cannonUpgradeInfoBlock->isVisible())
        cannonUpgradeInfoBlock->hide();
    
    /*if (selectedCell != UnselCell)
    {
        deselectCell();
        return;
    }*/

//    if (selectedCell == pos)
//        return;      

    int selX = pos.x();
    int selY = pos.y();
    if (cannons[selX][selY])
        if (cannonUpgradeInfoBlock->isVisible())
        {
            cannonUpgradeInfoBlock->hide();
        } else {
            cannonUpgradeInfoBlock->updatePosition(pos);
            cannonUpgradeInfoBlock->show();
        }
    else
    {
        cannonSelectionInfoBlock->updatePosition(pos);
        cannonSelectionInfoBlock->show();
    }
}

void CGame::deselectCell()
{
    cannonSelectionInfoBlock->hide();
    cannonUpgradeInfoBlock->hide();
}

QPoint CGame::findNearestCell(QPointF from)
{
    QPoint nearestCell(-1, -1);
    nearestCell.setX((from.x() - OffsetX) / CellSize);
    nearestCell.setY((from.y() - OffsetY) / CellSize);
    return nearestCell;
}

void CGame::onButtonPressed(int type)
{
    EButtonType eType = static_cast<EButtonType>(type);
    
    switch (eType)
    {
    case EButtonType::eBTgMenu:
        hide();
        endGame();
        view->gameMenu.show();
        break;
    default:
        break;
    }
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
        else
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
        else
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

    cannonsMutex.lock();

        for (int i = 0; i < CellNumX; ++i)
            for (int j = 0; j < CellNumY; ++j)
                if (cannons[i][j])
                {
                    cannons[i][j]->count();
                    cannons[i][j]->rotate();
                }

    cannonsMutex.unlock();

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
}

void CGame::onMousePressed(QMouseEvent *pressEvent)
{
    emit mousePressed(pressEvent);
}

void CGame::scaleObjects()
{
    background->scale();

    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->scale();

    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->scale();

    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->scale();

    cannonSelectionInfoBlock->scale();

    cannonUpgradeInfoBlock->scale();

    userInformationBlock->scale();

    waveInformationBlock->scale();
    
    menuButton->scale();
}
