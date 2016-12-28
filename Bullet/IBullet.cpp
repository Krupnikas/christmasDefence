#include "IBullet.h"
#include <Helper.h>
#include <Game/Game.h>
#include <Enemy/IEnemy.h>

QPointF IBullet::getCenter() const
{
    return center;
}

void IBullet::setCenter(const QPointF &value)
{
    center = value;
}

IBullet::~IBullet(){}

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
