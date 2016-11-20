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

void IBullet::draw(){}
bool IBullet::move(){}

void IBullet::onTimer(){}
