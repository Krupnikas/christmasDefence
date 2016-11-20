#pragma once

#include <Cannon/ICannon.h>

class CFastCannon : public ICannon
{
    
public:
    
    CFastCannon(CGame *game, int cellX, int cellY, double hp, double angle, double globalRadius);
    ~CFastCannon();
    
    virtual void fire(qreal angle) override;
    
    
public slots:
    virtual void onTimer();
    
};
