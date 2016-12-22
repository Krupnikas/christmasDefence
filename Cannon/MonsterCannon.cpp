#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/MonsterCannon.h>
#include <Bullet/MonsterBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CMonsterCannon::CMonsterCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    label = "Monster Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;

    textureSize = QSize(CellSize, CellSize);
    pixmap = &game->r->monster_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = SMALL;
    gameCell = cell;
    rotationSpeed = MonsterCannonSmRotation;
    fireSpeed = MonsterCannonSmFireSpeed;
    fireRadius = MonsterCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = MonsterCannonSmCost;
}

CMonsterCannon::~CMonsterCannon(){}

void CMonsterCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CMonsterBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
}

void CMonsterCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->user.getCash())
    {
        qDebug() << "Too expensive to upgrage MonsterCannon";
        return;
    }
    game->user.decreaseCash(upgradeCost);

    ICannon::upgrade();

    this->pixmap =
            helper::choose(
                            sizeType,
                            &game->r->monster_cannon_1,
                            &game->r->monster_cannon_2,
                            &game->r->monster_cannon_3);

    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);


    rotationSpeed =
            helper::choose(sizeType,
                            MonsterCannonSmRotation,
                            MonsterCannonMidRotation,
                            MonsterCannonBigRotation);
    fireSpeed =
            helper::choose(sizeType,
                            MonsterCannonSmFireSpeed,
                            MonsterCannonMidFireSpeed,
                            MonsterCannonBigFireSpeed);
    fireRadius =
            helper::choose(sizeType,
                            MonsterCannonSmRadius,
                            MonsterCannonMidRadius,
                            MonsterCannonBigRadius);

    radiusItem->upgrade(this);
    draw();
    show();
}

int CMonsterCannon::getUpgradeCost() const
{
    SizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          MonsterCannonSmCost,
                          MonsterCannonMidCost,
                          MonsterCannonBigCost);
}

int CMonsterCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          MonsterCannonSmCost,
                          MonsterCannonMidCost,
                          MonsterCannonBigCost);
}

qreal CMonsterCannon::getBulletSpeed() const
{
    return MonsterBulletStep;
}

qreal CMonsterCannon::getBulletRadius() const
{
    return std::min(MonsterBulletSizeY / 2, MonsterBulletSizeX / 2);
}

