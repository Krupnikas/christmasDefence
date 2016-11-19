#include <Bullet/FastBullet.h>
#include <Game/Game.h>

CFastBullet::CFastBullet(CGame *game, QPointF center, double angle)
{
    //IGameObject fields
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->size = QSize(BulletSizeX, BulletSizeY);
    this->pixmap = &game->r->fast_bullet_2;
    this->position = game->scene->addPixmap(size, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - position->boundingRect().width() / 2);
    this->leftTop.setY(center.y() - position->boundingRect().height() / 2);
    
    //IBullet fields
    this->step = FastBulletStep;
}

void CFastBullet::draw()
{
    game->scene->positionItem(leftTop, size, angle, zOrder, position);
}

void CFastBullet::move()
{
    center = helper::addVector(center, step, angle);
    leftTop = helper::addVector(leftTop, step, angle);
   /* if (!game->scene->insideGameRect(center))
        game->bullets.erase(iterator);*/
}
