#include <Enemy/FastEnemy.h>
#include <Game/Game.h>
#include <Game/Helper.h>


CFastEnemy::CFastEnemy(CGame *game, QPointF center, double angle)
{
    //IGameObject fields
    this->angle = angle;
    this->game = game;
    this->zOrder = 2;
    
    this->size = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_bullet_2;
    this->position = game->scene->addPixmap(size, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = FastBulletStep;
}

bool CFastEnemy::move()
{
    center = helper::addVector(center, game->scene->toGlobalCX(step), angle);
    leftTop = helper::addVector(leftTop, game->scene->toGlobalCX(step), angle);
    return game->scene->insideGameRect(center);
/*    {
        game->scene->removeItem(position);
    }*/
   /* if (!game->scene->insideGameRect(center))
        game->bullets.erase(iterator);*/
}

void CFastEnemy::onTimer()
{
    move();
    draw();
}
