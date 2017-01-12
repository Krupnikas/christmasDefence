#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/SlowCannon.h>
#include <Bullet/SlowBullet.h>
#include <Game/Game.h>
#include <Helper.h>

CSlowCannon::CSlowCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    label = "Slow Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;

    textureSize = QSize(game->CellSize, game->CellSize);
    pixmap = game->r->slow_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = ESizeType::eSmall;
    gameCell = cell;
    rotationSpeed = SlowCannonSmRotation;
    fireSpeed = SlowCannonSmFireSpeed;
    fireRadius = SlowCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = SlowCannonSmCost;
    sGunshot.setSource(game->r->url_gunshots[3]);
    sGunshot.setVolume(SoundLevel);
}

CSlowCannon::~CSlowCannon(){}

void CSlowCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CSlowBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
    
    QSoundEffect::Status status = sGunshot.status();
    sGunshot.play();
}

void CSlowCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->userManager.getCash())
    {
        qDebug() << "Too expensive to upgrage SlowCannon";
        return;
    }
    game->userManager.decreaseCash(upgradeCost);

    ICannon::upgrade();

    this->pixmap =
            helper::choose(
                            sizeType,
                            game->r->slow_cannon_1,
                            game->r->slow_cannon_2,
                            game->r->slow_cannon_3);

    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);


    rotationSpeed =
            helper::choose(sizeType,
                            SlowCannonSmRotation,
                            SlowCannonMidRotation,
                            SlowCannonBigRotation);
    fireSpeed =
            helper::choose(sizeType,
                            SlowCannonSmFireSpeed,
                            SlowCannonMidFireSpeed,
                            SlowCannonBigFireSpeed);
    fireRadius =
            helper::choose(sizeType,
                            SlowCannonSmRadius,
                            SlowCannonMidRadius,
                            SlowCannonBigRadius);

    radiusItem->upgrade(this);
    draw();
    show();
}

int CSlowCannon::getUpgradeCost() const
{
    ESizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          SlowCannonSmCost,
                          SlowCannonMidCost,
                          SlowCannonBigCost);
}

int CSlowCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          SlowCannonSmCost,
                          SlowCannonMidCost,
                          SlowCannonBigCost);
}

qreal CSlowCannon::getBulletSpeed() const
{
    return SlowBulletStep;
}

qreal CSlowCannon::getBulletRadius() const
{
    return std::min(SlowBulletSizeY / 2, SlowBulletSizeX / 2);
}

