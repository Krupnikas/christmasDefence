#include <Enemy/IEnemy.h>
#include <Enemy/Movements.h>

IEnemy::IEnemy(){}

IEnemy::~IEnemy(){}

bool IEnemy::move(){}

void IEnemy::die(){}

qreal IEnemy::getDistanceToFinish()
{
    return movements->getDistanceToFinish();
}

void IEnemy::updateDistances(){}

bool IEnemy::isDead() const
{
    return dead;
}

