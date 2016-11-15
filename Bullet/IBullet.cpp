#include "IBullet.h"

std::vector<std::shared_ptr<IBullet> >::iterator IBullet::getIterator() const
{
    return iterator;
}

void IBullet::setIterator(const std::vector<std::shared_ptr<IBullet> >::iterator &value)
{
    iterator = value;
}

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
void IBullet::move(){}
