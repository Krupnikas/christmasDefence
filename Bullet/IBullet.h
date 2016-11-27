#pragma once

#include <Game/Resource.h>
#include <Game/IGameObject.h>

class CGame;

class IBullet : public IGameObject
{     
    Q_OBJECT
    
public:
    
    virtual ~IBullet();

    virtual bool move();
    virtual bool reachedEnemy();
    
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
};
