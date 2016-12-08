#include <Cannon/ICannon.h>
#include <Cannon/CannonRadius.h>
#include <Enemy/FastEnemy.h>
#include <Game/Helper.h>
#include <Game/Game.h>

namespace
{

const qreal Epsilon = 0.5;

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

bool hits_(QPointF cannonCenter, qreal cannonAngle,
           QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
           qreal bulletSpeed, qreal bulletRadius)
{
    QLineF bulLine(cannonCenter, helper::addVector(cannonCenter, 50, cannonAngle));
    QLineF enLine(enemyCenter, enemyCenter + enemySpeed);
    QPointF intersect;
    if (bulLine.intersect(enLine, &intersect) != QLineF::NoIntersection)
    {
        int bulletStepsStart = std::floor((helper::manhattanLength(cannonCenter, intersect) - enemyRadius - bulletRadius) / bulletSpeed);
        int bulletStepsEnd = std::floor((helper::manhattanLength(cannonCenter, intersect) + enemyRadius + bulletRadius) / bulletSpeed);
        
        for (int step = bulletStepsStart; step <= bulletStepsEnd; ++step)
        {
            QPointF bulletPoint = helper::addVector(cannonCenter, step * bulletSpeed, cannonAngle);
            QPointF enemyPoint = enemyCenter + enemySpeed * step;
            if (helper::circlesIntersect(bulletPoint, bulletRadius, enemyPoint, enemyRadius))
                return true;
        }
        return false;
    }
    else
    {
        qDebug() << "ICannon: hits_: Bad parameters";
        return false;
    }
}

qreal bin_search_angle_clockwise_(QPointF cannonCenter,
                                  QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                                  qreal bulletSpeed, qreal bulletRadius)
{
    qreal left = helper::calcAngle(cannonCenter, enemyCenter);
    qreal right = left + 90;
    
    while (true)
    {
        qreal mid = (right + left) / 2;
        bool hits_mid = hits_(cannonCenter, mid, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius);
        bool hits_mid_eps = hits_(cannonCenter, mid + Epsilon, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius);
        if (hits_mid && !hits_mid_eps)
            return mid;
        if (hits_mid && hits_mid_eps)
            left = mid;
        else
            right = mid;
    }
}

qreal bin_search_angle_counter_clockwise_(QPointF cannonCenter,
                                  QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                                  qreal bulletSpeed, qreal bulletRadius)
{
    qreal right = helper::calcAngle(cannonCenter, enemyCenter) + 360;
    qreal left = right - 90;
    
    while (true)
    {
        qreal mid = (right + left) / 2;
        bool hits_mid = hits_(cannonCenter, mid, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius);
        bool hits_mid_eps = hits_(cannonCenter, mid - Epsilon, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius);
        if (hits_mid && !hits_mid_eps)
            return mid;
        if (hits_mid && hits_mid_eps)
            right = mid;
        else
            left = mid;
    }
}

qreal calc_desired_vector(QPointF cannonCenter,
                          QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                          qreal bulletSpeed, qreal bulletRadius)
{
    int clockwise = clockwise_movement_(cannonCenter, enemyCenter, enemySpeed);
    
    if (clockwise == 2)
        return helper::calcAngle(cannonCenter, enemyCenter);
    if (clockwise == 0)
        return bin_search_angle_clockwise_(cannonCenter,
                                           enemyCenter, enemySpeed, enemyRadius,
                                           bulletSpeed, bulletRadius);
    return bin_search_angle_counter_clockwise_(cannonCenter,
                                       enemyCenter, enemySpeed, enemyRadius,
                                       bulletSpeed, bulletRadius);
}

qreal calc_delta_angle(QPointF cannonCenter, qreal cannonAngle,
                       QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                       qreal bulletSpeed, qreal bulletRadius)
{
    
    qreal desiredAngle = calc_desired_vector(cannonCenter,
                                             enemyCenter, enemySpeed, enemyRadius,
                                             bulletSpeed, bulletRadius);
    
    QPointF pt1(helper::addVector(cannonCenter, 50, cannonAngle));
    QPointF pt2(helper::addVector(cannonCenter, 50, desiredAngle));
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

qreal ICannon::getBulletRadius() const
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
    
    qreal deltaAngle = calc_delta_angle(center, angle,
                                        curEnemy->getCenter(), curEnemy->getSpeed(), curEnemy->getSize().width(),
                                        getBulletSpeed(), getBulletRadius());
    if (abs(deltaAngle) <= rotationSpeed)
    {
        /*if (abs(deltaAngle) >= Epsilon)
        {
            angle = helper::calcAngle(game->scene->toGlobalPoint(center), 
                                      game->scene->toGlobalPoint(curEnemy->getCenter()));
            draw();
        }*/
        angle += deltaAngle;
        draw();
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

