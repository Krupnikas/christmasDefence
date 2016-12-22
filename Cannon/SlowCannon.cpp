#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/SlowCannon.h>
#include <Bullet/SlowBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CSlowCannon::CSlowCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    label = "Fast Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;

    textureSize = QSize(CellSize, CellSize);
    pixmap = &game->r->fast_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = SMALL;
    gameCell = cell;
    rotationSpeed = FastCannonSmRotation;
    fireSpeed = FastCannonSmFireSpeed;
    fireRadius = FastCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = FastCannonSmCost;
}

CSlowCannon::~CSlowCannon(){}

void CSlowCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CSlowBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
}

void CSlowCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->user.getCash())
    {
        qDebug() << "Too expensive to upgrage SlowCannon";
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

int CSlowCannon::getUpgradeCost() const
{
    SizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          FastCannonSmCost,
                          FastCannonMidCost,
                          FastCannonBigCost);
}

int CSlowCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          FastCannonSmCost,
                          FastCannonMidCost,
                          FastCannonBigCost);
}

qreal CSlowCannon::getBulletSpeed() const
{
    return FastBulletStep;
}

qreal CSlowCannon::getBulletRadius() const
{
    return std::min(FastBulletSizeY / 2, FastBulletSizeX / 2);
}

