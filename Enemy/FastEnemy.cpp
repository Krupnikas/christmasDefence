#include <Enemy/FastEnemy.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastEnemy::CFastEnemy(CGame *game)
{
    //IEnemy fields
    this->movements = std::shared_ptr<mov::Movements>(new mov::Movements(game));
    this->moveIter = movements->iterNum(FastEnemyStep);
    
    //IGameObject fields
    this->angle = movements->curAngle();
    this->center = movements->curCenter();
    this->leftTop.setX(center.x() - size.width() / 2);
    this->leftTop.setY(center.y() - size.height() / 2);
    
    this->game = game;
    this->zOrder = 2;
    
    this->size = FastEnemySize;
    this->pixmap = &game->r->fast_enemy_3;
    this->position = game->scene->addPixmap(size, pixmap);
    

}

bool CFastEnemy::move()
{
    for (int i = 0; i < 1/*moveIter*/; ++i)
        center = movements->move();
    angle = movements->curAngle();
    game->scene->positionItemByCenter(center, size, angle, zOrder, position);
    return game->scene->insideGameRect(center);
}

void CFastEnemy::die()
{
    dead = true;
}

void CFastEnemy::updateDistances()
{
    movements->updateNext();
}
