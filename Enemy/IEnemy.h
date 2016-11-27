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
    virtual void die();
    
    qreal getDistanceToFinish();
    
    QPoint getCurrentGameCell();
    QPoint getNextGameCell();

    virtual void updateDistances();
    
    
protected:
    std::shared_ptr<mov::Movements> movements;
    int moveIter;
    bool dead;
};
