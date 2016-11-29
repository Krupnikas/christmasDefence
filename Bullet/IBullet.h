#pragma once

#include <Game/Resource.h>
#include <Game/GameObject.h>

class CGame;

class IBullet : public CGameObject
{     
    Q_OBJECT
    
public:
    
    virtual ~IBullet();

    virtual bool move();
    
    bool reachedEnemy();
    
    //getters and setters
    int getX() const;
    void setX(int value);
    
    int getY() const;
    void setY(int value);
    
    QPointF getCenter() const;
    void setCenter(const QPointF &value);
    
public slots:
    virtual void onTimer();
    
protected:
    
    qreal step;
    int hitPower;
};
