#pragma once

#include <Resource.h>
#include <SceneObject/SceneObject.h>

class CGame;
class ICannon;

class IBullet : public CSceneObject
{     
    Q_OBJECT
    
public:
    
    IBullet();
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
    
protected:
    
    qreal step;
    int hitPower;
    
    std::shared_ptr<ICannon> sourceCannon;
    
};
