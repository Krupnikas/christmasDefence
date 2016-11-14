#include "ICannon.h"

int ICannon::getX() const
{
    return x;
}

void ICannon::setX(int value)
{
    x = value;
}

int ICannon::getY() const
{
    return y;
}

void ICannon::setY(int value)
{
    y = value;
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

ICannon::~ICannon() {}

void ICannon::draw(){}
void ICannon::fire(){}
