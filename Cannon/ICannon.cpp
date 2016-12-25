#include <Cannon/ICannon.h>
#include <Cannon/CannonRadius.h>
#include <Enemy/FastEnemy.h>
#include <Game/Helper.h>
#include <Game/Game.h>

namespace
{

const qreal EpsilonAngle = 0.1;
const qreal DeltaAngle = 1;
const qreal SpeedDiv = 20;

qreal calc_mid_(qreal left, qreal right)
{
    if (left > right)
        right += 360;
    qreal mid = (left + right) / 2;
    if (mid > 360)
        mid -= 360;
    return mid;
}

//1 - clockwise, 0 - counter-clockwise, 2 - going away
int clockwise_movement_(QPointF p1, QPointF p2, QPointF p2Vect)
{
    QLineF line1(p2, p1);
    QLineF line2(p2, p2 + p2Vect);
    qreal angle = line2.angleTo(line1);
    if (angle >= 355 || angle <= 5 ||
        (angle >= 175 && angle <= 185))
        return 2;
    if (angle > 185)
        return 1;

    return 0;
}

bool hits_(QPointF cannonCenter, qreal cannonAngle,
           QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
           qreal bulletSpeed, qreal bulletRadius, CGame *game)
{
    bulletSpeed = game->scene->toGlobalDist(bulletSpeed, cannonAngle) / SpeedDiv;
    enemySpeed.setX(enemySpeed.x() / SpeedDiv);
    enemySpeed.setY(enemySpeed.y() / SpeedDiv);

    QLineF bulLine(cannonCenter, helper::addVector(cannonCenter, 50, cannonAngle));
    QLineF enLine(enemyCenter, enemyCenter + enemySpeed * 100);
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

qreal bin_search_angle_(QPointF cannonCenter,
                                  QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                                  qreal bulletSpeed, qreal bulletRadius, CGame *game, bool clockwise)
{
    qreal left = 0;
    qreal right = 0;

    if (clockwise)
    {
        left = helper::calcAngle(cannonCenter, enemyCenter);
        right = left + 90;
        if (right > 360)
            right -= 360;
    }
    else
    {
        right = helper::calcAngle(cannonCenter, enemyCenter);
        left = right - 90;
        if (left < 0)
            left += 360;
    }

    while (std::abs(right - left) > EpsilonAngle)
    {
        qreal mid = calc_mid_(left, right);

        qreal mid_delt = mid + (clockwise ? DeltaAngle : -DeltaAngle);
        if (mid_delt > 360)
            mid_delt -= 360;
        if (mid_delt < 0)
            mid_delt += 360;

        qreal mid_delt_eps = mid_delt + (clockwise ? EpsilonAngle : -EpsilonAngle);
        if (mid_delt_eps > 360)
            mid_delt_eps -= 360;
        if (mid_delt_eps < 0)
            mid_delt_eps += 360;

        bool hits_mid = hits_(cannonCenter, mid, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius, game);
        bool hits_mid_delt = hits_(cannonCenter, mid_delt, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius, game);
        bool hits_mid_delt_eps = hits_(cannonCenter, mid_delt_eps, enemyCenter, enemySpeed, enemyRadius, bulletSpeed, bulletRadius, game);
        if (hits_mid && hits_mid_delt && !hits_mid_delt_eps)
            return mid;
        if (hits_mid && hits_mid_delt && hits_mid_delt_eps)
        {
            if (clockwise)
                left = mid;
            else
                right = mid;
        }
        else
        {
            if (clockwise)
                right = mid;
            else
                left = mid;
        }
    }
    left = right;
}

qreal calc_desired_vector(QPointF cannonCenter,
                          QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                          qreal bulletSpeed, qreal bulletRadius, CGame *game)
{
    int clockwise = clockwise_movement_(cannonCenter, enemyCenter, enemySpeed);
    
    if (clockwise == 2)
        return helper::calcAngle(cannonCenter, enemyCenter);

    return bin_search_angle_(cannonCenter,
                                       enemyCenter, enemySpeed, enemyRadius,
                                       bulletSpeed, bulletRadius, game, clockwise);
}

qreal calc_delta_angle(QPointF cannonCenter, qreal cannonAngle,
                       QPointF enemyCenter, QPointF enemySpeed, qreal enemyRadius,
                       qreal bulletSpeed, qreal bulletRadius, CGame *game)
{
    
    qreal desiredAngle = calc_desired_vector(cannonCenter,
                                             enemyCenter, enemySpeed, enemyRadius,
                                             bulletSpeed, bulletRadius, game);
    
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

bool ICannon::isRadiusVisible()
{
    return this->radiusItem->isVisible();
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

eSizeType ICannon::getSizeType() const
{
    return sizeType;
}

eSizeType ICannon::getUpgradeSizeType() const
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
    
    qreal deltaAngle = calc_delta_angle(game->scene->toGlobalPoint(center), angle,
                                        game->scene->toGlobalPoint(curEnemy->getCenter()),
                                        game->scene->toGlobalSize(curEnemy->getSpeed()),
                                        game->scene->toGlobalCX(curEnemy->getSize().width() / 20),
                                        getBulletSpeed(),
                                        game->scene->toGlobalCX(getBulletRadius()),
                                        game);
    if (std::abs(deltaAngle) <= rotationSpeed)
    {
        /*if (std::abs(deltaAngle) >= Epsilon)
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

