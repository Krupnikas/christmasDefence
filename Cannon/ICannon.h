#pragma once

#include <Game/Resource.h>

class Game;

class ICannon : public QObject
{     
    Q_OBJECT
    
protected:
    
    QGraphicsItem *position;
    
    int cellX;
    int cellY;
    
    QPoint center;
    QPoint leftTop;
    
    double hp;
    double angle;
    double globalRadius;  
    Game *game;
    
public:
    
    virtual ~ICannon();

    virtual void draw();
    virtual void fire(qreal angle);
    
    //getters and setters
    int getX() const;
    void setX(int value);
    
    int getY() const;
    void setY(int value);
    
    double getHp() const;
    void setHp(double value);
    
    double getAngle() const;
    void setAngle(double value);
    
    double getGlobalRadius() const;
    void setGlobalRadius(double value);
    
    QPoint getCenter() const;
    void setCenter(const QPoint &value);
    
public slots:
    virtual void rotate();
};

#include <Game/Game.h>
