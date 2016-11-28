#pragma once

#include <Game/IGameObject.h>
#include <Enemy/Movements.h>

class IEnemy : public IGameObject
{
    Q_OBJECT
public:

    IEnemy();
    ~IEnemy();
    
    virtual bool move();
    
    bool isDead() const;
    void hit(int hpDiff);
    
    qreal getDistanceToFinish();
    
    QPoint getCurrentGameCell() const;
    QPoint getNextGameCell() const;

    virtual void updateDistances();
    
    
protected:
    std::shared_ptr<mov::Movements> movements;
    int moveIter;
    
    int hp;
    bool dead;
};
