#include <Bullet/BurnBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>


CBurnBullet::CBurnBullet(CGame *game, QPointF center, double angle, eSizeType type)
{
    //IGameObject fields
    this->label = "Burn Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(BurnBulletSizeX, BurnBulletSizeY);
    this->pixmap = helper::choose(type,
                                  &game->r->burn_bullet_1,
                                  &game->r->burn_bullet_2,
                                  &game->r->burn_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = BurnBulletStep;
    this->hitPower = helper::choose(type, BurnBulletSmHit, BurnBulletMidHit, BurnBulletBigHit);
}

bool CBurnBullet::move()
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



void CBurnBullet::onTimer()
{
    move();
    draw();
}
