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
    
    virtual void fire() = 0;
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

    bool isRadiusVisible();
    
    //IGameObject methods override
    virtual void scaleItem() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;
    
    //ICannon own virtual methods    
    virtual int getUpgradeCost() const;
    virtual int getCurCost() const;
    virtual qreal getBulletSpeed() const;
    virtual qreal getBulletRadius() const;
    
    eSizeType getSizeType() const;
    eSizeType getUpgradeSizeType() const;
    
protected:
    eSizeType sizeType;
    QPoint gameCell;
    qreal hp;
    qreal rotationSpeed;
    int fireSpeed;
    qreal fireRadius;
    
    std::shared_ptr<CCannonRadius> radiusItem;
    bool toShowRadius = false;
    
    std::shared_ptr<IEnemy> curEnemy;
    
    int cost;
    
private:
    bool reachingEnemy(std::shared_ptr<IEnemy> enemy);
    void findEnemy();
    
private:
    int counter = 0;
};
