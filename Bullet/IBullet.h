#pragma once

#include <Game/Resource.h>
#include <Game/GameObject.h>

class CGame;

class IBullet : public CGameObject
{     
    Q_OBJECT
    
public:
    
    virtual ~IBullet();

    virtual bool move() = 0;
    
    bool reachedEnemy();
    
    //getters and setters
    int getX() const;
    void setX(int value);
    
    int getY() const;
    void setY(int value);
    
    QPointF getCenter() const;
    void setCenter(const QPointF &value);
    
protected:
    
    qreal step;
    int hitPower;
};
