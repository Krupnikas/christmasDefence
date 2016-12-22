#pragma once

#include <Bullet/IBullet.h>

class CMonsterBullet : public IBullet
{
public:
    
    CMonsterBullet(CGame *game, QPointF center, double angle, SizeType type);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
