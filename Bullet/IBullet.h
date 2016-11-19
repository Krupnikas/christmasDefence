#pragma once

#include <Game/Resource.h>
#include <Game/IGameObject.h>

class CGame;

class IBullet : public IGameObject
{     
    Q_OBJECT
    
protected:
    
    std::vector<std::shared_ptr<IBullet>>::iterator iterator;
    
    qreal step;
    
public:
    
    virtual ~IBullet();

    virtual void draw();
    virtual void move();
    
    //getters and setters
    int getX() const;
    void setX(int value);
    
    int getY() const;
    void setY(int value);
    
    std::vector<std::shared_ptr<IBullet> >::iterator getIterator() const;
    void setIterator(const std::vector<std::shared_ptr<IBullet> >::iterator &value);
    QPointF getCenter() const;
    void setCenter(const QPointF &value);
};
