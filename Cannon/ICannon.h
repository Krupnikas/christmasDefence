#pragma once

#include <Game/IGameObject.h>

class CGame;

class ICannon : public IGameObject
{     
    Q_OBJECT
    
protected:
    int cellX;
    int cellY;
    double hp;
    double globalRadius;  
    
public:
    
    ICannon();
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
    
public slots:
    virtual void onTimer();
};
