#include <Cannon/FastCannon.h>

FastCannon::FastCannon(Game *game, int x, int y)
{
    this->game = game;
    this->x = x;
    this->y = y;
}

FastCannon::~FastCannon()
{
    
}

void FastCannon::draw()
{
    game->scene->drawPixmap(OffsetX + x * CellSize, y * CellSize , CellSize, CellSize, game->r->fast_cannon_3, angle);
}

void FastCannon::fire()
{
    
}
