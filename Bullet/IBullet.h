#pragma once

#include <Game/Resource.h>

class Game;

class IBullet : public QObject
{     
    Q_OBJECT
    
protected:
    
    QGraphicsItem *position;
    
    QPointF center;
    QPointF leftTop;
    
    std::vector<std::shared_ptr<IBullet>>::iterator iterator;
    
    qreal angle;
    qreal step;
    Game *game;
    
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

#include <Game/Game.h>
