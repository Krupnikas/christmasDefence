#pragma once

#include <Cannon/ICannon.h>

class CSlowCannon : public ICannon
{

public:

    CSlowCannon(CGame *game, QPoint cell, double angle);
    ~CSlowCannon();

    //IGameObject methods override
    virtual void fire() override;
    virtual void upgrade() override;

    //ICannon own virtual methods
    virtual int getUpgradeCost() const override;
    virtual int getCurCost() const override;
    virtual qreal getBulletSpeed() const override;
    virtual qreal getBulletRadius() const override;
};
