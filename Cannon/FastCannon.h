#pragma once

#include <Cannon/ICannon.h>

class CFastCannon : public ICannon
{
    
public:
    
    CFastCannon(CGame *game, QPoint cell, double angle);
    ~CFastCannon();
    
    //IGameObject methods override
    virtual void fire() override;
    virtual void upgrade() override;
    
    //ICannon own virtual methods    
    virtual int getUpgradeCost() const;
    virtual int getCurCost() const;
    virtual qreal getBulletSpeed() const;
};
