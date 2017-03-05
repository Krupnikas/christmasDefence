#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Helper.h>

CFastCannon::CFastCannon(CGame *game, QPoint cell, double angle)
{
    //CSceneObject fields
    label = "Fast Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;
    
    textureSize = QSize(m::CellSize, m::CellSize);
    pixmap = game->r->fast_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);
    
    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);
    
    //ICannon fields
    sizeType = ESizeType::eSmall;
    gameCell = cell;
    rotationSpeed = m::FastCannonSmRotation;
    fireSpeed = m::FastCannonSmFireSpeed;
    fireRadius = m::FastCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));
    
    cost = m::FastCannonSmCost;
    
    //sGunshot.setSource(game->r->url_gunshots[1]);
    //sGunshot.setVolume(m::SoundLevel);
}

CFastCannon::~CFastCannon(){}

void CFastCannon::fire()
{
    std::shared_ptr<IBullet> bullet = 
            std::make_shared<CFastBullet>(game, game->cannons[gameCell.x()][gameCell.y()], this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
    
    QSoundEffect::Status status = sGunshot.status();
    //sGunshot.play();
}

void CFastCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->userManager.getCash())
    {
        qDebug() << "Too expensive to upgrage FastCannon";
        return;
    }
    game->userManager.decreaseCash(upgradeCost);
    
    ICannon::upgrade();
    
    this->pixmap = 
            helper::choose(
                            sizeType, 
                            game->r->fast_cannon_1, 
                            game->r->fast_cannon_2, 
                            game->r->fast_cannon_3);
                
    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);
    
    
    rotationSpeed = 
            helper::choose(sizeType, 
                            m::FastCannonSmRotation,
                            m::FastCannonMidRotation,
                            m::FastCannonBigRotation);
    fireSpeed = 
            helper::choose(sizeType,
                            m::FastCannonSmFireSpeed,
                            m::FastCannonMidFireSpeed,
                            m::FastCannonBigFireSpeed);
    fireRadius = 
            helper::choose(sizeType,
                            m::FastCannonSmRadius,
                            m::FastCannonMidRadius,
                            m::FastCannonBigRadius);
    
    radiusItem->upgrade(this);
    draw();
    show();
}

int CFastCannon::getUpgradeCost() const
{
    ESizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          m::FastCannonSmCost,
                          m::FastCannonMidCost,
                          m::FastCannonBigCost);
}

int CFastCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          m::FastCannonSmCost,
                          m::FastCannonMidCost,
                          m::FastCannonBigCost);
}

qreal CFastCannon::getBulletSpeed() const
{
    return m::FastBulletStep;
}

qreal CFastCannon::getBulletRadius() const
{
    return std::min(m::FastBulletSizeY / 2, m::FastBulletSizeX / 2);
}

