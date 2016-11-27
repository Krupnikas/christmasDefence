#pragma once

#include <Cannon/ICannon.h>

class CFastCannon : public ICannon
{
    
public:
    
    CFastCannon(CGame *game, QPoint cell, double angle);
    ~CFastCannon();
    
    virtual void fire(qreal angle) override;
    
};
