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
    
std::vector<QPoint> generate_cells_(int edge, int pos)
{
    std::vector<QPoint> cells;
    
    int xMid = (m::CellNumX - 1) / 2;
    int xLess = rand() % xMid;
    int xGr = xMid + rand() % (m::CellNumX - xMid - 1) + 1;
    
    int yMid = (m::CellNumY - 1) / 2;
    int yLess = rand() % yMid;
    int yGr = yMid + rand() % (m::CellNumY - yMid) + 1;

    
    switch (edge) {
    case 0: //left
        if (pos == 0)
            cells.push_back(QPoint(0, yGr));
        else if (pos == 1)
        {
            cells.push_back(QPoint(0, yMid));
            if (m::CellNumY % 2 == 0)
                cells.push_back(QPoint(0, yMid + 2));
        }
        else
            cells.push_back(QPoint(0, yLess));
        break;
    case 1: //top
        if (pos == 0)
            cells.push_back(QPoint(xLess, 0));
        else if (pos == 1)
        {
            cells.push_back(QPoint(xMid - 1, 0));
            if (m::CellNumX % 2 == 0)
                cells.push_back(QPoint(xMid + 2, 0));
        }
        else
            cells.push_back(QPoint(xGr, 0));
        break;
    case 2: //right
    {
        int x = m::CellNumX - 1;
        if (pos == 0)
            cells.push_back(QPoint(x, yLess));
        else if (pos == 1)
        {
            cells.push_back(QPoint(x, yMid));
            if (m::CellNumY % 2 == 0)
                cells.push_back(QPoint(x, yMid + 2));
        }
        else
            cells.push_back(QPoint(x, yGr));
        break;
    }
    case 3: //bottom
    {
        int y = m::CellNumY - 1;
        if (pos == 0)
            cells.push_back(QPoint(xGr, y));
        else if (pos == 1)
        {
            cells.push_back(QPoint(xMid - 1, y));
            if (m::CellNumX % 2 == 0)
                cells.push_back(QPoint(xMid + 2, y));
        }
        else
            cells.push_back(QPoint(xLess, y));
        break;
    }
    default:
        break;
    }
    
    
    return cells;
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
    calculator(this),
    selectionStatus(ESelectionStatus::eNone)
{
    pressedButton = EButtonType::eBTnone;

    positionTimer = new QTimer(this);
    drawTimer = new QTimer(this);

    connect(positionTimer, SIGNAL(timeout()), &calculator, SLOT(start()));
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
    
    userManager.setCash(20000);
    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
        {
            bool buy = rand() % 2;
            if (buy)
                buyCannon(std::make_shared<CFastCannon>(this, QPoint(i, j), 45));
        }
    
    waveManager.initialize();
    helper::updateDistances(cannons, distances);

    positionTimer->start(m::PositionTimerInterval);
    drawTimer->start(m::DrawTimerInterval);
    
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
    return helper::cellToEdge(cell) == EEdge::eInside;
}

bool CGame::buyCannon(std::shared_ptr<ICannon> cannon)
{
    QPoint cell = cannon->getGameCell();
    int x = cell.x();
    int y = cell.y();

    int cost = cannon->getCurCost();

    if (!isGameCell(cell) ||
        !helper::okToAdd(cell, distances, enemies) ||
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
    nearestCell.setX((from.x() - m::OffsetX) / m::CellSize + 1);
    nearestCell.setY((from.y() - m::OffsetY) / m::CellSize + 1);
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
        view->gameMenu.create();
        view->gameMenu.show();
        break;
    default:
        break;
    }
}

void CGame::onPositionTimer()
{

}

void CGame::onDrawTimer()
{
    //view->setGraphicsViewUpdatesEnabled(false);

    for (size_t i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();

    for (auto enemy: enemies)
        enemy->draw();

    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
            if (cannons[i][j])
                cannons[i][j]->draw();

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

    //view->setGraphicsViewUpdatesEnabled(true);
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
    m::startCells = generate_cells_(edge, pos);
    
    //end cell
    line = textStream.readLine();
    in.clear();
    in.str(line.toStdString());
    in >> edge >> pos;
    m::endCells = generate_cells_(edge, pos);
    
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
