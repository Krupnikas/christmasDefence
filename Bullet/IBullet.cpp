#include "IBullet.h"

QPointF IBullet::getCenter() const
{
    return center;
}

void IBullet::setCenter(const QPointF &value)
{
    center = value;
}


IBullet::~IBullet(){}

bool IBullet::move(){}

bool IBullet::reachedEnemy(){}

void IBullet::onTimer(){}
