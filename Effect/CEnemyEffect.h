#pragma once

#include <Effect/CEffect.h>

class IEnemy;

class CEnemyEffect: public CEffect
{
public:
    CEnemyEffect();
    
    std::shared_ptr<IEnemy> getEnemy() const;
    void setEnemy(const std::shared_ptr<IEnemy> &value);
    
    virtual void beforeEffect() override;
    virtual void onEffect() override;
    virtual void afterEffect() override;
    
private:
    std::shared_ptr<IEnemy> enemy;
    bool enemySet;
};

