#include <mainview.h>
#include <Cannon/CannonRadius.h>
#include <Cannon/MonsterCannon.h>
#include <Bullet/MonsterBullet.h>
#include <Game/Game.h>
#include <Helper.h>

CMonsterCannon::CMonsterCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    label = "Monster Cannon";
    this->angle = angle;
    this->game = game;
    zOrder = 2;

    textureSize = QSize(m::CellSize, m::CellSize);
    pixmap = game->r->monster_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);

    leftTop = game->cellLeftTop(cell);
    center = game->cellCenter(cell);

    //ICannon fields
    sizeType = ESizeType::eSmall;
    gameCell = cell;
    rotationSpeed = m::MonsterCannonSmRotation;
    fireSpeed = m::MonsterCannonSmFireSpeed;
    fireRadius = m::MonsterCannonSmRadius;
    radiusItem = std::make_shared<CCannonRadius>(dynamic_cast<ICannon *>(this));

    cost = m::MonsterCannonSmCost;
    sGunshot.setSource(game->r->url_gunshots[2]);
    sGunshot.setVolume(m::SoundLevel);
}

CMonsterCannon::~CMonsterCannon(){}

void CMonsterCannon::fire()
{
    std::shared_ptr<IBullet> bullet =
            std::make_shared<CMonsterBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
    sGunshot.play();
}

void CMonsterCannon::upgrade()
{
    int upgradeCost = getUpgradeCost();
    if (upgradeCost > game->userManager.getCash())
    {
        qDebug() << "Too expensive to upgrage MonsterCannon";
        return;
    }
    game->userManager.decreaseCash(upgradeCost);

    ICannon::upgrade();

    this->pixmap =
            helper::choose(
                            sizeType,
                            game->r->monster_cannon_1,
                            game->r->monster_cannon_2,
                            game->r->monster_cannon_3);

    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);


    rotationSpeed =
            helper::choose(sizeType,
                            m::MonsterCannonSmRotation,
                            m::MonsterCannonMidRotation,
                            m::MonsterCannonBigRotation);
    fireSpeed =
            helper::choose(sizeType,
                            m::MonsterCannonSmFireSpeed,
                            m::MonsterCannonMidFireSpeed,
                            m::MonsterCannonBigFireSpeed);
    fireRadius =
            helper::choose(sizeType,
                            m::MonsterCannonSmRadius,
                            m::MonsterCannonMidRadius,
                            m::MonsterCannonBigRadius);

    radiusItem->upgrade(this);
    draw();
    show();
}

int CMonsterCannon::getUpgradeCost() const
{
    ESizeType upSizeType = getUpgradeSizeType();
    return helper::choose(upSizeType,
                          m::MonsterCannonSmCost,
                          m::MonsterCannonMidCost,
                          m::MonsterCannonBigCost);
}

int CMonsterCannon::getCurCost() const
{
    return helper::choose(sizeType,
                          m::MonsterCannonSmCost,
                          m::MonsterCannonMidCost,
                          m::MonsterCannonBigCost);
}

qreal CMonsterCannon::getBulletSpeed() const
{
    return m::MonsterBulletStep;
}

qreal CMonsterCannon::getBulletRadius() const
{
    return std::min(m::MonsterBulletSizeY / 2, m::MonsterBulletSizeX / 2);
}

