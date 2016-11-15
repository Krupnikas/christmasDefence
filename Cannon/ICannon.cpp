#include "ICannon.h"

int ICannon::getX() const
{
    return cellX;
}

void ICannon::setX(int value)
{
    cellX = value;
}

int ICannon::getY() const
{
    return cellY;
}

void ICannon::setY(int value)
{
    cellY = value;
}

double ICannon::getHp() const
{
    return hp;
}

void ICannon::setHp(double value)
{
    hp = value;
}

double ICannon::getAngle() const
{
    return angle;
}

void ICannon::setAngle(double value)
{
    angle = value;
}

double ICannon::getGlobalRadius() const
{
    return globalRadius;
}

void ICannon::setGlobalRadius(double value)
{
    globalRadius = value;
}

QPoint ICannon::getCenter() const
{
    return center;
}

void ICannon::setCenter(const QPoint &value)
{
    center = value;
}

ICannon::~ICannon() {}

void ICannon::draw(){}
void ICannon::fire(qreal angle){}
void ICannon::rotate(){}
