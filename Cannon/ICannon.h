#pragma once

#include <Game/GameObject.h>

class CGame;
class IEnemy;
class CCannonRadius;

class ICannon : public CGameObject
{     
    Q_OBJECT
        
public:
    
    ICannon();
    virtual ~ICannon();
    
    virtual void fire();
    virtual void upgrade();
    
    void rotate();
    void count();
    void showRadius();
    void hideRadius();
    
    //getters and setters
    QPoint getGameCell() const;
    void setGameCell(const QPoint &value);
    
    double getHp() const;
    void setHp(double value);
    
    double getFireRadius() const;
    void setFireRadius(double value);
    
    //IGameObject methods override
    virtual void scaleItem();
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;
    
protected:
    SizeType sizeType;
    QPoint gameCell;
    qreal hp;
    qreal rotationSpeed;
    int fireSpeed;
    qreal fireRadius;
    
    std::shared_ptr<CCannonRadius> radiusItem;
    bool toShowRadius = false;
    
    std::shared_ptr<IEnemy> curEnemy;
    
private:
    bool reachingEnemy(std::shared_ptr<IEnemy> enemy);
    void findEnemy();
    
private:
    int counter = 0;
    const int Epsilon = 0.5;
};
