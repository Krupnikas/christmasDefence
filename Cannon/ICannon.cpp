#include <Cannon/ICannon.h>
#include <Cannon/CannonRadius.h>
#include <Enemy/FastEnemy.h>
#include <Game/Helper.h>
#include <Game/Game.h>

ICannon::ICannon() : radiusItem(nullptr), curEnemy(nullptr) {}
ICannon::~ICannon() {}

QPoint ICannon::getGameCell() const
{
    return gameCell;
}

void ICannon::setGameCell(const QPoint &value)
{
    gameCell = value;
}

double ICannon::getHp() const
{
    return hp;
}

void ICannon::setHp(double value)
{
    hp = value;
}

double ICannon::getFireRadius() const
{
    return fireRadius;
}

void ICannon::setFireRadius(double value)
{
    fireRadius = value;
}

void ICannon::scaleItem()
{
    CGameObject::scaleItem();
    radiusItem->scaleItem();
}

void ICannon::draw()
{
    CGameObject::draw();
    radiusItem->draw();
}

void ICannon::hide()
{
    CGameObject::hide();
    radiusItem->hide();
}

void ICannon::show()
{
    CGameObject::show();
    if (toShowRadius)
        radiusItem->show();
}

SizeType ICannon::getSizeType() const
{
    return sizeType;
}

SizeType ICannon::getUpgradeSizeType() const
{
    if (sizeType == SMALL)
        return MEDIUM;
    else
        return BIG;
}

int ICannon::getUpgradeCost() const
{
    return 0;   
}

int ICannon::getCurCost() const
{
    return 0;
}

bool ICannon::reachingEnemy(std::shared_ptr<IEnemy> enemy)
{
    qreal length = helper::manhattanLength(center, enemy->getCenter());
    return length <= (enemy->getSize().width() / 2 + fireRadius);
}

void ICannon::findEnemy()
{
    qreal minDist = std::numeric_limits<int>::max();
    std::shared_ptr<IEnemy> minEnemy = nullptr;
    for (std::shared_ptr<IEnemy> enemy: game->enemies)
    {
        if (enemy->isDead())
            continue;
        if (reachingEnemy(enemy)) 
        {
            qreal distToFinish = enemy->getDistanceToFinish();
            if (distToFinish < minDist)
            {
                minDist = distToFinish;
                minEnemy = enemy;
            }
        }
    }

    curEnemy = minEnemy;
}

void ICannon::fire(){}

void ICannon::upgrade()
{
    sizeType = getUpgradeSizeType();
    counter = 0;
}

void ICannon::showRadius()
{
    radiusItem->show();
    toShowRadius = true;
}

void ICannon::hideRadius()
{
    radiusItem->hide();
    toShowRadius = false;
}

void ICannon::rotate()
{
    if (!curEnemy)
        findEnemy();
    else
    {
        if (curEnemy->isDead() || !reachingEnemy(curEnemy))
        {
            findEnemy();
        }
    }
    
    if (!curEnemy)
        return;
    
    qreal deltaAngle = helper::calcAngle(center, curEnemy->getCenter(), angle);
    if (abs(deltaAngle) <= rotationSpeed)
    {
        if (abs(deltaAngle) >= Epsilon)
        {
            angle = helper::calcAngle(game->scene->toGlobalPoint(center), 
                                      game->scene->toGlobalPoint(curEnemy->getCenter()));
            draw();
        }
        if (counter == fireSpeed)
        {
            fire();
            counter = 0;
        }
    }
    else
    {
        //helper::reconcileAngles(angle, deltaAngle, rotationSpeed);
        if (deltaAngle > 0)
            angle += rotationSpeed;
        else
            angle -= rotationSpeed;
        draw();
    }
    
    
}

void ICannon::count()
{
    if (counter < fireSpeed)
        counter++;
}

