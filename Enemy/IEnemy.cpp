#include <Enemy/IEnemy.h>
#include <Enemy/Movements.h>

IEnemy::IEnemy(){}

IEnemy::~IEnemy(){}

bool IEnemy::move(){}

bool IEnemy::isDead() const
{
    return dead;
}

void IEnemy::hit(int hpDiff)
{
    hp -= hpDiff;
    if (hp <= 0)
        dead = true;
}

qreal IEnemy::getDistanceToFinish()
{
    return movements->getDistanceToFinish();
}

QPoint IEnemy::getCurrentGameCell() const
{
    return movements->getCurrentGameCell();
}

QPoint IEnemy::getNextGameCell() const
{
    return movements->getNextGameCell();
}

void IEnemy::updateDistances(){}



