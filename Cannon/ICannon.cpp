#include "ICannon.h"
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

double ICannon::getGlobalRadius() const
{
    return fireRadius;
}

void ICannon::setGlobalRadius(double value)
{
    fireRadius = value;
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
    if (sizeType == SMALL)
        sizeType = MEDIUM;
    else if (sizeType == MEDIUM)
        sizeType = BIG;
    counter = 0;
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
            if (game->enemies.size() < 5)
                game->addEnemy(std::make_shared<CFastEnemy>(game));
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

void ICannon::showRadius()
{
    game->scene->positionItemByCenter(center, QSizeF(fireRadius * 2, fireRadius * 2),
                                      0, zOrder - 0.1, radiusItem);
    radiusItem->setFlag(QGraphicsItem::ItemHasNoContents, false);
    radiusItem->show();
    qDebug() << radiusItem.get();
}

void ICannon::hideRadius()
{
    radiusItem->hide();
    radiusItem->setFlag(QGraphicsItem::ItemHasNoContents, true);
}
