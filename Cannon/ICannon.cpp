#include "ICannon.h"

ICannon::ICannon(){}
ICannon::~ICannon() {}

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

double ICannon::getGlobalRadius() const
{
    return globalRadius;
}

void ICannon::setGlobalRadius(double value)
{
    globalRadius = value;
}

void ICannon::draw(){}
void ICannon::fire(qreal angle){}
void ICannon::onTimer(){}
