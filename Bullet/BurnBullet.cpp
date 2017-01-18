#include <Bullet/BurnBullet.h>
#include <Game/Game.h>
#include <Helper.h>
#include <Enemy/IEnemy.h>
#include <Cannon/ICannon.h>


CBurnBullet::CBurnBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type)
{
    //IGameObject fields
    this->label = "Burn Bullet";
    this->angle = angle;
    this->game = game;
    this->zOrder = 1;
    
    this->textureSize = QSize(m::BurnBulletSizeX, m::BurnBulletSizeY);
    this->pixmap = helper::choose(type,
                                  game->r->burn_bullet_1,
                                  game->r->burn_bullet_2,
                                  game->r->burn_bullet_3);
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = cannon->getCenter();
    this->leftTop.setX(center.x() - game->scene->toLocalCX(position->boundingRect().width()) / 2);
    this->leftTop.setY(center.y() - game->scene->toLocalCY(position->boundingRect().height()) / 2);
    
    //IBullet fields
    step = m::BurnBulletStep;
    hitPower = helper::choose(type, m::BurnBulletSmHit, m::BurnBulletMidHit, m::BurnBulletBigHit);
    sourceCannon = cannon;
}
