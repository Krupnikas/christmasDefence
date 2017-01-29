#include "IBullet.h"
#include <Helper.h>
#include <Game/Game.h>
#include <Enemy/IEnemy.h>
#include <Cannon/ICannon.h>
#include <mainview.h>

QPointF IBullet::getCenter() const
{
    return center;
}

void IBullet::setCenter(const QPointF &value)
{
    center = value;
}

IBullet::IBullet(){}

IBullet::~IBullet(){}

bool IBullet::move()
{
    center = helper::addVector(center, game->scene->toGlobalDist(step, angle), angle);
    leftTop = helper::addVector(leftTop, game->scene->toGlobalDist(step, angle), angle);
    
    qreal dist = helper::manhattanLength(center, sourceCannon->getCenter());
    qreal radius = sourceCannon->getFireRadius();
    qreal disappearStart = radius * m::BulletDisappearStart;
    qreal disappearEnd = radius * m::BulletDisappearEnd;
    //if (dist > disappearStart)
    //    position->setOpacity((disappearEnd - dist) / (disappearEnd - disappearStart));
    
    return game->scene->insideEnclosingRect(center) &&
             dist <= disappearEnd;
}

bool IBullet::reachedEnemy()
{
    for (auto enemy: game->enemies)
    {
        qreal length = helper::manhattanLength(center, enemy->getCenter());
        if (length <= textureSize.width() / 2 + enemy->getSize().width() / 2)
        {
            enemy->hit(hitPower);
            return true;
        }
    }
    
    return false;
}
