#include <Effect/CEnemyEffect.h>

CEnemyEffect::CEnemyEffect():
    enemySet(false)
{}

std::shared_ptr<IEnemy> CEnemyEffect::getEnemy() const
{
    if (!enemySet)
        return nullptr;
    return enemy;
}

void CEnemyEffect::setEnemy(const std::shared_ptr<IEnemy> &value)
{
    enemy = value;
    enemySet = value != nullptr;
}

void CEnemyEffect::beforeEffect()
{
    
}

void CEnemyEffect::onEffect()
{
    
}

void CEnemyEffect::afterEffect()
{
    
}

