#pragma once

#include <Game/IGameObject.h>

class CGame;
class IEnemy;

class ICannon : public IGameObject
{     
    Q_OBJECT
        
public:
    
    ICannon();
    virtual ~ICannon();

    virtual void fire(qreal angle);
    
    void showRadius();
    void hideRadius();
    void rotate();
    void count();
    
    //getters and setters
    QPoint getGameCell() const;
    void setGameCell(const QPoint &value);
    
    double getHp() const;
    void setHp(double value);
    
    double getGlobalRadius() const;
    void setGlobalRadius(double value);
    

    
protected:
    QPoint gameCell;
    qreal hp;
    qreal rotationSpeed;
    int fireSpeed;
    qreal globalRadius;
    std::shared_ptr<QGraphicsItem> radiusItem;
    
    std::shared_ptr<IEnemy> curEnemy;
    
private:
    int counter = 0;
    
    const int Epsilon = 0.5;
};
