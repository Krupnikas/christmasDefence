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
    
protected:
    std::shared_ptr<Movements> movements;
};
