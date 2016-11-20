#pragma once

#include <Game/IGameObject.h>

class CGame;

class CFastEnemy : public IGameObject
{
public:
    
    CFastEnemy(CGame *game, QPointF center, double angle);
    
    virtual bool move();
    
public slots:
    virtual void onTimer();
};
