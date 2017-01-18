#include <Bullet/MonsterBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>
#include <Cannon/ICannon.h>

CMonsterBullet::CMonsterBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type)
{
    //IGameObject fields
    this->label = "Monster Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(m::MonsterBulletSizeX, m::MonsterBulletSizeY);
    this->pixmap = helper::choose(type,
                                  game->r->monster_bullet_1,
                                  game->r->monster_bullet_2,
                                  game->r->monster_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = cannon->getCenter();
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    step = m::MonsterBulletStep;
    hitPower = helper::choose(type, m::MonsterBulletSmHit, m::MonsterBulletMidHit, m::MonsterBulletBigHit);
    sourceCannon = cannon;
}
