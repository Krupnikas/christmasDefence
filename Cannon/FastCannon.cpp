#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>

FastCannon::FastCannon(Game *game, int x, int y, double hp, double angle, double globalRadius)
{
    this->game = game;
    this->cellX = x;
    this->cellY = y;
    this->hp = hp;
    this->angle = angle;
    this->globalRadius = globalRadius;
    this->leftTop = QPoint(OffsetX + cellX * CellSize, cellY * CellSize);
    this->center = QPoint(OffsetX + cellX * CellSize + CellSize / 2, cellY * CellSize + CellSize / 2);
    position = nullptr;
}

FastCannon::~FastCannon()
{
    
}

void FastCannon::draw()
{
    if (!position)
        position = game->scene->drawPixmap(CellSize, CellSize, game->r->fast_cannon_2);
    game->scene->positionItem(OffsetX + cellX * CellSize, cellY * CellSize, 
                              CellSize, CellSize, angle, 2, position);
}

void FastCannon::fire(qreal angle)
{
    std::shared_ptr<IBullet> bullet = std::make_shared<FastBullet>(game, center.x(), center.y(), angle);
    game->bullets.push_back(bullet);
    bullet->setIterator(game->bullets.end() - 1);
}

void FastCannon::rotate()
{
    QPoint p = game->view->mapFromGlobal(QCursor::pos());
    int x1 = game->scene->toGlobalX(center.x());
    int y1 = game->scene->toGlobalY(center.y());
    angle = helper::calcAngle(x1, y1, p.x(), p.y());
    draw();
}
