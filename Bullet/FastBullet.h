#pragma once

#include <Bullet/IBullet.h>

class CFastBullet : public IBullet
{
public:
    
    CFastBullet(CGame *game, QPointF center, double angle, SizeType type);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
