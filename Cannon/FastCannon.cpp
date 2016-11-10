#include <Cannon/FastCannon.h>

FastCannon::FastCannon(Game *game)
{
    this->game = game;
}

FastCannon::~FastCannon()
{
    
}

void FastCannon::draw()
{
    game->scene->drawPixmap(100, 100, 300, 300, game->r->fast_cannon_3);
}

void FastCannon::fire()
{
    
}
