#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/BurnCannon.h>
#include <Bullet/BurnBullet.h>
#include <Game/Game.h>
#include <Helper.h>

CBurnCannon::CBurnCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    label = "Burn Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;

    textureSize = QSize(CellSize, CellSize);
    pixmap = &game->r->burn_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = SMALL;
    gameCell = cell;
    rotationSpeed = BurnCannonSmRotation;
    fireSpeed = BurnCannonSmFireSpeed;
    fireRadius = BurnCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = BurnCannonSmCost;
}

CBurnCannon::~CBurnCannon(){}

void CBurnCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CBurnBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
}

void CBurnCannon::upgrade()
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
                            &game->r->burn_cannon_1,
                            &game->r->burn_cannon_2,
                            &game->r->burn_cannon_3);

    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);


    rotationSpeed =
            helper::choose(sizeType,
                            BurnCannonSmRotation,
                            BurnCannonMidRotation,
                            BurnCannonBigRotation);
    fireSpeed =
            helper::choose(sizeType,
                            BurnCannonSmFireSpeed,
                            BurnCannonMidFireSpeed,
                            BurnCannonBigFireSpeed);
    fireRadius =
            helper::choose(sizeType,
                            BurnCannonSmRadius,
                            BurnCannonMidRadius,
                            BurnCannonBigRadius);

    radiusItem->upgrade(this);
    draw();
    show();
}

int CBurnCannon::getUpgradeCost() const
{
    eSizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          BurnCannonSmCost,
                          BurnCannonMidCost,
                          BurnCannonBigCost);
}

int CBurnCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          BurnCannonSmCost,
                          BurnCannonMidCost,
                          BurnCannonBigCost);
}

qreal CBurnCannon::getBulletSpeed() const
{
    return BurnBulletStep;
}

qreal CBurnCannon::getBulletRadius() const
{
    return std::min(BurnBulletSizeY / 2, BurnBulletSizeX / 2);
}

