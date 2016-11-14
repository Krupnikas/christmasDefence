#include <Cannon/FastCannon.h>

FastCannon::FastCannon(Game *game, int x, int y, double hp, double angle, double globalRadius)
{
    this->game = game;
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->angle = angle;
    this->globalRadius = globalRadius;
}

FastCannon::~FastCannon()
{
    
}

void FastCannon::draw()
{
    game->scene->drawPixmap(OffsetX + x * CellSize, y * CellSize , CellSize, CellSize, 
                            game->r->fast_cannon_2, angle);
}

void FastCannon::fire()
{
    
}

void FastCannon::rotate()
{
    angle = int((angle + 3)) % 360;
    draw();
}
