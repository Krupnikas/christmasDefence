#include <Cannon/FastCannon.h>

FastCannon::FastCannon(Game *game, int x, int y, double hp, double angle, double globalRadius)
{
    this->game = game;
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->angle = angle;
    this->globalRadius = globalRadius;
    position = nullptr;
}

FastCannon::~FastCannon()
{
    
}

void FastCannon::draw()
{
    if (!position)
        position = game->scene->drawPixmap(CellSize, CellSize, game->r->fast_cannon_2);
    game->scene->positionItem(OffsetX + x * CellSize, y * CellSize, CellSize, CellSize, angle, position);
}

void FastCannon::fire()
{
    
}

void FastCannon::rotate()
{
    QPoint p = game->view->mapFromGlobal(QCursor::pos());
    int x1 = game->scene->toGlobalX(OffsetX + x * CellSize + CellSize / 2);
    int y1 = game->scene->toGlobalY(y * CellSize + CellSize / 2);
    angle = helper::calcAngle(x1, y1, p.x(), p.y());
    draw();
}
