#pragma once

#include <Bullet/IBullet.h>

class CSlowBullet : public IBullet
{
public:
    
    CSlowBullet(CGame *game, QPointF center, double angle, ESizeType type);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
