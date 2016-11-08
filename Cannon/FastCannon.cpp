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
    QGraphicsPixmapItem *item = game->gameScene->addPixmap(game->r->fast_cannon_3);
    item->setPos(100, 100);
}

void FastCannon::fire()
{
    
}
