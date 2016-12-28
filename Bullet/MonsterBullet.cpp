#include <Bullet/MonsterBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>


CMonsterBullet::CMonsterBullet(CGame *game, QPointF center, double angle, eSizeType type)
{
    //IGameObject fields
    this->label = "Monster Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(MonsterBulletSizeX, MonsterBulletSizeY);
    this->pixmap = helper::choose(type,
                                  &game->r->monster_bullet_1,
                                  &game->r->monster_bullet_2,
                                  &game->r->monster_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = center;
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    this->step = MonsterBulletStep;
    this->hitPower = helper::choose(type, MonsterBulletSmHit, MonsterBulletMidHit, MonsterBulletBigHit);
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
