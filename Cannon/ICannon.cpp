#include "ICannon.h"
#include <Enemy/FastEnemy.h>
#include <Game/Helper.h>
#include <Game/Game.h>

ICannon::ICannon() : curEnemy(nullptr) {}
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
    return globalRadius;
}

void ICannon::setGlobalRadius(double value)
{
    globalRadius = value;
}

void ICannon::fire(qreal angle){}

void ICannon::rotate()
{
    if (curEnemy && !curEnemy->isDead())
    {
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
                fire(angle);
                counter = 0;
            }
        }
        else
        {
            //helper::reconcileAngles(angle, deltaAngle, rotationSpeed);
            angle += deltaAngle;
            draw();
        }
    }
    else
    {
        qreal minDist = std::numeric_limits<int>::max();
        std::shared_ptr<IEnemy> minEnemy = nullptr;
        for (std::shared_ptr<IEnemy> enemy: game->enemies)
        {
            qreal length = helper::manhattanLength(center, enemy->getCenter());
            if (length <= (enemy->getSize().width() / 2 + globalRadius)) 
            {
                qreal distToFinish = enemy->getDistanceToFinish();
                if (distToFinish < minDist)
                {
                    minDist = distToFinish;
                    minEnemy = enemy;
                }
            }
        }
        if (curEnemy && curEnemy->isDead() && (game->enemies.size() < 5))
            game->addEnemy(std::make_shared<CFastEnemy>(game));
        curEnemy = minEnemy;
    }
    
    
}

void ICannon::count()
{
    if (counter < fireSpeed)
        counter++;
}

void ICannon::showRadius()
{
    game->scene->positionItemByCenter(center, QSizeF(FastCannonRadius * 2, FastCannonRadius * 2),
                                      0, zOrder - 0.1, radiusItem);
    radiusItem->show();
    qDebug() << radiusItem.get();
}

void ICannon::hideRadius()
{
    radiusItem->hide();
}
