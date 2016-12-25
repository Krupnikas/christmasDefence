#include <Bullet/MonsterBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>
#include <Enemy/IEnemy.h>


CMonsterBullet::CMonsterBullet(CGame *game, QPointF center, double angle, SizeType type)
{
    //IGameObject fields
    this->label = "Fast Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(FastBulletSizeX, FastBulletSizeY);
    this->pixmap = helper::choose(type,
                                  &game->r->fast_bullet_1,
                                  &game->r->fast_bullet_2,
                                  &game->r->fast_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = FastBulletStep;
    this->hitPower = helper::choose(type, FastBulletSmHit, FastBulletMidHit, FastBulletBigHit);
}

bool CMonsterBullet::move()
{
    center = helper::addVector(center, game->scene->toGlobalDist(step, angle), angle);
    leftTop = helper::addVector(leftTop, game->scene->toGlobalDist(step, angle), angle);
    return game->scene->insideEnclosingRect(center);
}



void CMonsterBullet::onTimer()
{
    move();
    draw();
}
