#pragma once

#include <Game/GameObject.h>
#include <Enemy/Movements.h>

class CHpBackground;
class CHpCurrent;

class IEnemy : public CGameObject
{
    Q_OBJECT
public:

    IEnemy();
    ~IEnemy();
    virtual bool move();
    
    bool isDead() const;
    void hit(int hpDiff);
    void updateHpPos();
    void updateHpSize(); //expensive, uses QTransform
    
    qreal getDistanceToFinish() const;
    QPoint getCurrentGameCell() const;
    QPoint getNextGameCell() const;
    QPointF getSpeed() const;
    
    //IGameObject methods override
    virtual void scaleItem() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

protected:
    virtual QPixmap *getTexture(int enemyTexture);
    
protected:
    std::shared_ptr<mov::Movements> movements;
    int moveIter;
    
    int hpCur;
    int hpMax;
    bool dead;
    
    std::shared_ptr<CHpCurrent> hpCurItem;
    std::shared_ptr<CHpBackground> hpBackgroundItem;
};
