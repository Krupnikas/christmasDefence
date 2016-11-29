#pragma once

#include <Game/IGameObject.h>
#include <Enemy/Movements.h>

class CHpBackground;
class CHpCurrent;

class IEnemy : public IGameObject
{
    Q_OBJECT
public:

    IEnemy();
    ~IEnemy();
    
    //IGameObject methods override
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;
    
    virtual bool move();
    
    bool isDead() const;
    void hit(int hpDiff);
    void updateHp();
    
    qreal getDistanceToFinish();
    
    QPoint getCurrentGameCell() const;
    QPoint getNextGameCell() const;

protected:
    std::shared_ptr<mov::Movements> movements;
    int moveIter;
    
    int hpCur;
    int hpMax;
    bool dead;
    
    std::shared_ptr<CHpCurrent> hpCurItem;
    std::shared_ptr<CHpBackground> hpBackgroundItem;
};
