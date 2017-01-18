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

    textureSize = QSize(m::CellSize, m::CellSize);
    pixmap = game->r->burn_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = ESizeType::eSmall;
    gameCell = cell;
    rotationSpeed = m::BurnCannonSmRotation;
    fireSpeed = m::BurnCannonSmFireSpeed;
    fireRadius = m::BurnCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = m::BurnCannonSmCost;
    sGunshot.setSource(game->r->url_gunshots[0]);
    sGunshot.setVolume(m::SoundLevel);
}

CBurnCannon::~CBurnCannon(){}

void CBurnCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CBurnBullet>(game, game->cannons[gameCell.x()][gameCell.y()], this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
    sGunshot.play();
}

void CBurnCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->userManager.getCash())
    {
        qDebug() << "Too expensive to upgrage BurnCannon";
        return;
    }
    game->userManager.decreaseCash(upgradeCost);

    ICannon::upgrade();

    this->pixmap =
            helper::choose(
                            sizeType,
                            game->r->burn_cannon_1,
                            game->r->burn_cannon_2,
                            game->r->burn_cannon_3);

    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);


    rotationSpeed =
            helper::choose(sizeType,
                            m::BurnCannonSmRotation,
                            m::BurnCannonMidRotation,
                            m::BurnCannonBigRotation);
    fireSpeed =
            helper::choose(sizeType,
                            m::BurnCannonSmFireSpeed,
                            m::BurnCannonMidFireSpeed,
                            m::BurnCannonBigFireSpeed);
    fireRadius =
            helper::choose(sizeType,
                            m::BurnCannonSmRadius,
                            m::BurnCannonMidRadius,
                            m::BurnCannonBigRadius);

    radiusItem->upgrade(this);
    draw();
    show();
}

int CBurnCannon::getUpgradeCost() const
{
    ESizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          m::BurnCannonSmCost,
                          m::BurnCannonMidCost,
                          m::BurnCannonBigCost);
}

int CBurnCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          m::BurnCannonSmCost,
                          m::BurnCannonMidCost,
                          m::BurnCannonBigCost);
}

qreal CBurnCannon::getBulletSpeed() const
{
    return m::BurnBulletStep;
}

qreal CBurnCannon::getBulletRadius() const
{
    return std::min(m::BurnBulletSizeY / 2, m::BurnBulletSizeX / 2);
}

