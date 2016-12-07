#include <Cannon/ICannon.h>
#include <Cannon/CannonRadius.h>
#include <Enemy/FastEnemy.h>
#include <Game/Helper.h>
#include <Game/Game.h>

namespace
{

//0 - clockwise, 1 - counter-clockwise, 2 - away
int clockwise_movement_(QPointF p1, QPointF p2, QPointF p2Vect)
{
    QLineF line1(p2, p1);
    QLineF line2(p2, p2Vect);
    qreal angle = line2.angleTo(line1);
    if (angle > 185)
        return 0;
    if (angle < 175)
        return 1;
    return 2;
}

qreal calc_desired_vector(QPointF cannonCenter, qreal cannonAngle, QPointF enemyCenter, QPointF enemySpeed, qreal bulletSpeed)
{
    int clockwise = clockwise_movement_(cannonCenter, enemyCenter, enemySpeed);
    
    if (clockwise == 2)
        return helper::calcAngle(cannonCenter, enemyCenter);
    
    
}

qreal calc_delta_angle(QPointF cannonCenter, qreal cannonAngle, QPointF enemyCenter, QPointF enemySpeed, qreal bulletSpeed)
{
    
    qreal desiredAngle = calc_desired_vector(cannonCenter, cannonAngle, enemyCenter, enemySpeed, bulletSpeed);
    
    QPointF pt1(addVector(cannonCenter, 50, cannonAngle));
    QPointF pt2(addVector(cannonCenter, 50, desiredAngle));
    QLineF currentLine(cannonCenter, pt1);
    QLineF desiredLine(cannonCenter, pt2);
    qreal deltaAngle = desiredLine.angleTo(currentLine);
    if (deltaAngle > 180)
        deltaAngle -= 360;
    return deltaAngle;
}

}

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

qreal ICannon::getBulletSpeed() const
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
    
    qreal deltaAngle = helper::calcAngle(center, getBulletSpeed(), curEnemy->getCenter(), curEnemy->getSpeed(), angle);
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

