#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>
#include <Enemy/IEnemy.h>


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
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = FastBulletStep;
}

bool CFastBullet::move()
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

bool CFastBullet::reachedEnemy()
{
    for (auto enemy: game->enemies)
    {
        qreal enemyZ = enemy->getZOrder();
        enemy->setZOrder(zOrder);   
        QList<QGraphicsItem *> list(enemy->getPosition()->collidingItems(Qt::ContainsItemBoundingRect));
        QList<QGraphicsItem *> list1(position->collidingItems(Qt::ContainsItemBoundingRect));
        if (position->collidesWithItem(enemy->getPosition().get()/*, Qt::ContainsItemShape*/))
        {
            enemy->die();
            return true;
        }
        enemy->setZOrder(enemyZ);
    }
    
    return false;
}

void CFastBullet::onTimer()
{
    move();
    draw();
}
