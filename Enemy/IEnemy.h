#pragma once

#include <SceneObject/SceneObject.h>
#include <Enemy/Movements.h>

class CHpBackground;
class CHpCurrent;

class IEnemy : public CSceneObject
{
    Q_OBJECT
public:

    IEnemy();
    ~IEnemy();
    virtual bool move();
    
    bool isDead() const;
    void hit(int hpDiff);
    void updateHpPos();
    void updateHpSize(); //expensive, uses QTransform
    
    qreal getDistanceToFinish() const;
    QPoint getCurrentGameCell() const;
    QPoint getNextGameCell() const;
    bool beforeTurnArea() const;
    QPointF getSpeed() const;
    bool getWasInsideGame();
    bool getWasOutsideGame();
    
    //IGameObject methods override
    virtual void scale() override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;

protected:
    virtual std::shared_ptr<QPixmap> getTexture(int enemyTexture) = 0;
    
protected:
    std::shared_ptr<mov::Movements> movements;
    int moveIter;
    
    int hpCur;
    int hpMax;
    bool dead;
    bool wasInsideGame;
    bool wasOutsideGame;
    
    std::shared_ptr<CHpCurrent> hpCurItem;
    std::shared_ptr<CHpBackground> hpBackgroundItem;

};
