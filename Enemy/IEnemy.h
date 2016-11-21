#pragma once

#include <Game/IGameObject.h>

class IEnemy : public IGameObject
{
protected:
    
    
public:

    IEnemy();
    ~IEnemy();
    
virtual bool move();
    
public slots:
    virtual void onTimer();
    
protected:
    
    qreal angleDesired;
    int cellXCur;
    int cellYCur;
    int cellXNext;
    int cellYNext;
    QLineF trajectory;
};
