#include <Bullet/SlowBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>


CSlowBullet::CSlowBullet(CGame *game, QPointF center, double angle, ESizeType type)
{
    //IGameObject fields
    this->label = "Slow Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(m::SlowBulletSizeX, m::SlowBulletSizeY);
    this->pixmap = helper::choose(type,
                                  game->r->slow_bullet_1,
                                  game->r->slow_bullet_2,
                                  game->r->slow_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = m::SlowBulletStep;
    this->hitPower = helper::choose(type, m::SlowBulletSmHit, m::SlowBulletMidHit, m::SlowBulletBigHit);
}

bool CSlowBullet::move()
{
    center = helper::addVector(center, game->scene->toGlobalDist(step, angle), angle);
    leftTop = helper::addVector(leftTop, game->scene->toGlobalDist(step, angle), angle);
    return game->scene->insideEnclosingRect(center);
/*    {
        game->scene->removeItem(position);
    }*/
   /* if (!game->scene->insideGameRect(center))
        game->bullets.erase(iterator);*/
}



void CSlowBullet::onTimer()
{
    move();
    draw();
}
