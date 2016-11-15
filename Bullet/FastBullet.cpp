#include <Bullet/FastBullet.h>

FastBullet::FastBullet(Game *game, int x, int y, double angle)
{
    this->position = nullptr;
    this->center = QPoint(x, y);
    this->angle = angle;
    this->step = FastBulletStep;
    this->game = game;
}

void FastBullet::draw()
{
    if (!position)
    {
        position = game->scene->drawPixmap(BulletSizeX, BulletSizeY, game->r->fast_bullet_2);
        this->leftTop.setX(center.x() - position->boundingRect().width() / 2);
        this->leftTop.setY(center.y() - position->boundingRect().height() / 2);
    }
    game->scene->positionItem(leftTop.x(), leftTop.y(), BulletSizeX, BulletSizeX, angle, 1, position);
}

void FastBullet::move()
{
    center = helper::addVector(center, step, angle);
    leftTop = helper::addVector(leftTop, step, angle);
   /* if (!game->scene->insideGameRect(center))
        game->bullets.erase(iterator);*/
}
