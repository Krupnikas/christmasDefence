#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>
#include <Cannon/ICannon.h>


CFastBullet::CFastBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type)
{
    //IGameObject fields
    this->label = "Fast Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(m::FastBulletSizeX, m::FastBulletSizeY);
    this->pixmap = helper::choose(type,
                                  game->r->fast_bullet_1,
                                  game->r->fast_bullet_2,
                                  game->r->fast_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = cannon->getCenter();
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    step = m::FastBulletStep;
    hitPower = helper::choose(type, m::FastBulletSmHit, m::FastBulletMidHit, m::FastBulletBigHit);
    sourceCannon = cannon;
}
