#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastCannon::CFastCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    this->label = "Fast Cannon";
    this->angle = angle;
    this->game = game;
    this->zOrder = 2;
    
    this->textureSize = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);
    
    this->leftTop = game->cellLeftTop(cell);
    this->center = game->cellCenter(cell);
    
    //ICannon fields
    this->sizeType = SMALL;
    this->gameCell = cell;
    this->rotationSpeed = FastCannonSmRotation;
    this->fireSpeed = FastCannonSmFireSpeed;
    this->fireRadius = FastCannonSmRadius;
    this->radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));
    hideRadius();
    
    cost = FastCannonSmCost;
}

CFastCannon::~CFastCannon(){}

void CFastCannon::fire()
{
    std::shared_ptr<IBullet> bullet = 
            std::make_shared<CFastBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
}

void CFastCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->user.getCash())
    {
        qDebug() << "Too expensive to upgrage FastCannon";
        return;
    }
    game->user.decreaseCash(upgradeCost);
    
    ICannon::upgrade();
    
    this->pixmap = 
            helper::choose(
                            sizeType, 
                            &game->r->fast_cannon_1, 
                            &game->r->fast_cannon_2, 
                            &game->r->fast_cannon_3);
                
    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);
    
    
    rotationSpeed = 
            helper::choose(sizeType, 
                            FastCannonSmRotation,
                            FastCannonMidRotation,
                            FastCannonBigRotation);
    fireSpeed = 
            helper::choose(sizeType,
                            FastCannonSmFireSpeed,
                            FastCannonMidFireSpeed,
                            FastCannonBigFireSpeed);
    fireRadius = 
            helper::choose(sizeType,
                            FastCannonSmRadius,
                            FastCannonMidRadius,
                            FastCannonBigRadius);
    
    radiusItem->upgrade(this);
    draw();
    show();
}

int CFastCannon::getUpgradeCost() const
{
    SizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          FastCannonSmCost,
                          FastCannonMidCost,
                          FastCannonBigCost);
}

int CFastCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          FastCannonSmCost,
                          FastCannonMidCost,
                          FastCannonBigCost);
}

qreal CFastCannon::getBulletSpeed() const
{
    return FastBulletStep;
}

qreal CFastCannon::getBulletRadius() const
{
    return std::min(FastBulletSizeY / 2, FastBulletSizeX / 2);
}

