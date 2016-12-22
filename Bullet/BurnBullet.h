#pragma once

#include <Bullet/IBullet.h>

class CBurnBullet : public IBullet
{
public:
    
    CBurnBullet(CGame *game, QPointF center, double angle, SizeType type);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
