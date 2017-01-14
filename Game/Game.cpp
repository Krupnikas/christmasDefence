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
#include <Game/WaveManager.h>
#include <SceneObject/Button.h>

namespace
{
    
QPoint generate_cell_(int edge, int pos, int cellNumX, int cellNumY)
{
    int x = -1;
    int y = -1;
    
    int xMid = (cellNumX - 1) / 2;
    int xLess = rand() % xMid;
    int xGr = xMid + rand() % (cellNumX - xMid - 1) + 1;
    
    int yMid = (cellNumY - 1) / 2;
    int yLess = rand() % yMid;
    int yGr = yMid + rand() & (cellNumY - yMid) + 1;

    
    switch (edge) {
    case 0: //left
        x = 0;
        y = (pos == 1) ? yMid : ((pos == 0) ? yGr : yLess);
        break;
    case 1: //top
        y = 0;
        x = (pos == 1) ? xMid : ((pos == 0) ? xLess : xGr);
        break;
    case 2: //right
        x = cellNumX - 1;
        y = (pos == 1) ? yMid : ((pos == 0) ? yLess : yGr);
        break;
    case 3: //bottom
        y = cellNumY - 1;
        x = (pos == 1) ? xMid : ((pos == 0) ? xGr : xLess);
        break;
    default:
        break;
    }
    
    return QPoint(x, y);
}

}

CGame::CGame(MainView *view, R *r, CScene *scene, QMediaPlaylist *playlist, QMediaPlayer *player):
    view(view),
    r(r),
    scene(scene),
    playlist(playlist),
    player(player),
    waveManager(this),
    userManager(this),
    selectionStatus(ESelectionStatus::eNone)
{
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
                m::BackgroundZOrder + 0.3,
                QPointF(m::OffsetX / 2, m::LocalHeight - m::CellSize / 2),
                QSizeF(m::CellSize * 0.7, m::CellSize * 0.7),
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
    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
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
    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->hide();
    
    scene->removeFPS();
    scene->removeWaveInfo();
    
    view->app->installEventFilter(view);
}

void CGame::resize()
{
    scale_objects_();
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
    //waveManager and userManager's fields are initialized here
    QString filename = r->levels + QString::number(level) + QString(".txt");
    read_level_(filename);
    
    create();

    cannons.resize(m::CellNumX);
    distances.resize(m::CellNumX);
    for (int i = 0; i < m::CellNumX; ++i)
    {
        cannons[i].assign(m::CellNumY, nullptr);
        distances[i].resize(m::CellNumY);
    }
    
    waveManager.initialize();
    helper::updateDistances(cannons, distances);

    positionTimer->start(m::TimerInterval);
    drawTimer->start(m::TimerInterval);
    
    show();
}

void CGame::endGame()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->remove();
    bullets.clear();

    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->remove();
    enemies.clear();

    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
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
    return cell.x() >= 0 && cell.x() < m::CellNumX && cell.y() >= 0 && cell.y() < m::CellNumY;
}

bool CGame::buyCannon(std::shared_ptr<ICannon> cannon)
{
    QPoint cell = cannon->getGameCell();
    int x = cell.x();
    int y = cell.y();

    int cost = cannon->getCurCost();

    if (x < 0 || x > m::CellNumX   ||
        y < 0 || y > m::CellNumY   ||
        !helper::okToAdd(x, y, distances, enemies) ||
        cost > userManager.getCash())
        return false;

    userManager.decreaseCash(cost);

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
    userManager.increaseCash(cannon->getCurCost() / 4.0 * 3);
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
    qreal x = 0;
    if (cell.x() > 0)
        x = m::OffsetX + (cell.x() - 1) * m::CellSize;
    
    qreal y = 0;
    if (cell.y() > 0)
        y = m::OffsetY + (cell.y() - 1) * m::CellSize;
    return QPointF(x, y);
}

QSizeF CGame::cellSize(QPoint cell)
{
    EEdge edge(helper::cellToEdge(cell));
    if (edge == EEdge::eLeft || edge == EEdge::eRight)
        return QSizeF(m::OffsetX, m::CellSize);
    else if (edge == EEdge::eTop || edge == EEdge::eBottom)
        return QSizeF(m::CellSize, m::OffsetY);
    else
        return QSizeF(m::CellSize, m::CellSize);
}

QPointF CGame::cellCenter(QPoint cell)
{
    QPointF leftTop(cellLeftTop(cell));
    QSizeF size(cellSize(cell));
    return QPointF(leftTop.x() + size.width() / 2.0, leftTop.y() + size.height() / 2.0);
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
    nearestCell.setX(from.x() / m::CellSize);
    nearestCell.setY(from.y() / m::CellSize);
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

        for (int i = 0; i < m::CellNumX; ++i)
            for (int j = 0; j < m::CellNumY; ++j)
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

void CGame::scale_objects_()
{
    background->scale();

    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->scale();

    for (size_t i = 0; i < enemies.size(); ++i)
        enemies[i]->scale();

    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->scale();

    cannonSelectionInfoBlock->scale();

    cannonUpgradeInfoBlock->scale();

    userInformationBlock->scale();

    waveInformationBlock->scale();
    
    menuButton->scale();
}

void CGame::read_level_(QString filename)
{
    QFile levelFile(filename);
    if (!levelFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "CLevelManager: read_file_: failed to open " << filename;
        return;
    }
    QTextStream textStream(&levelFile);
    QString line;
    
    //field size init
    line = textStream.readLine();
    m::CellNumY = line.toInt();
    
    //init game metrics
    helper::initMetrics();
    

    //start cell
    line = textStream.readLine();
    std::stringstream in(line.toStdString());
    int edge, pos;
    in >> edge >> pos;
    m::startCell = generate_cell_(edge, pos, m::CellNumX, m::CellNumY);
    
    //end cell
    line = textStream.readLine();
    in.clear();
    in.str(line.toStdString());
    in >> edge >> pos;
    m::endCell = generate_cell_(edge, pos, m::CellNumX, m::CellNumY);
    
    //TODO : init field with items
    line = textStream.readLine();
    
    //waves init
    line = textStream.readLine();
    int waveNum(line.toInt());
    
    waveManager.waves.clear();
    for (int i = 0; i < waveNum; ++i)
    {
        CWave wave;        
        line = textStream.readLine();
        std::stringstream in(line.toStdString());
        
        in >> wave.timeBeforeStart;
        in >> wave.enemyIncomeInterval;
        in >> wave.totalEnemyNum;
        in >> wave.enemyType;
        in >> wave.enemyTexture;
        in >> wave.enemyPower;
        waveManager.waves.push_back(wave);        
    }
    
    //user init
    line = textStream.readLine();
    in.clear();
    in.str(line.toStdString());
    int cash, hp;
    in >> cash >> hp;
    userManager.setCash(cash);
    userManager.setHp(hp);
    
    levelFile.close();
}
