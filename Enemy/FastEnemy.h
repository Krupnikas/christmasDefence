#pragma once

#include <Enemy/IEnemy.h>

class CGame;

const qreal Delta = 10;

class CFastEnemy : public IEnemy
{
public:
    
    CFastEnemy(CGame *game, QPointF center, double angle);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
    
};
