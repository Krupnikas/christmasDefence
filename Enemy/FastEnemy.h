#pragma once

class CFastEnemy
{
public:
    
    CFastEnemy(CGame *game, QPointF center, double angle);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
