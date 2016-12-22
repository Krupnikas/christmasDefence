#pragma once

#include <Cannon/ICannon.h>

class CBurnCannon : public ICannon
{

public:

    CBurnCannon(CGame *game, QPoint cell, double angle);
    ~CBurnCannon();

    //IGameObject methods override
    virtual void fire() override;
    virtual void upgrade() override;

    //ICannon own virtual methods
    virtual int getUpgradeCost() const override;
    virtual int getCurCost() const override;
    virtual qreal getBulletSpeed() const override;
    virtual qreal getBulletRadius() const override;
};
