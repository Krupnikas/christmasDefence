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
    virtual void updateDistances();
    
protected:
    std::shared_ptr<mov::Movements> movements;
};
