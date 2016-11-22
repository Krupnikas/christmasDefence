#include <mainview.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastCannon::CFastCannon(CGame *game, int cellX, int cellY, double hp, double angle, double globalRadius)
{
    //IGameObject fields
    this->angle = angle;
    this->game = game;
    this->zOrder = 2;
    
    this->size = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_cannon_2;
    position = game->scene->addPixmap(size, pixmap);
    
    this->leftTop = QPointF(OffsetX + cellX * CellSize, OffsetY + cellY * CellSize);
    this->center = QPointF(leftTop.x() + size.width() / 2, leftTop.y() + size.height() / 2);
    
    //ICannon fields
    this->cellX = cellX;
    this->cellY = cellY;
    this->hp = hp;
    this->globalRadius = globalRadius;
}

CFastCannon::~CFastCannon(){}

void CFastCannon::fire(qreal angle)
{
    std::shared_ptr<IBullet> bullet = std::make_shared<CFastBullet>(game, center, angle);
    game->bullets.push_back(bullet);
    //connect(game->gameTimer, SIGNAL(timeout()), bullet.get(), SLOT(onTimer()));
}

void CFastCannon::onTimer()
{
    QPoint p = game->view->mapFromGlobal(QCursor::pos());
    int x1 = game->scene->toGlobalX(center.x());
    int y1 = game->scene->toGlobalY(center.y());
    angle = helper::calcAngle(x1, y1, p.x(), p.y());
    draw();
    //qreal scaleFactor = angle / 360.0;
    //scaleItem(scaleFactor);
}
