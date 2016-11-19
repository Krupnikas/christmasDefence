#pragma once

#include <Cannon/ICannon.h>

class CSlowCannon : public ICannon
{
private:
    
public:
    
    CSlowCannon();
    ~CSlowCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
    
public slots:
    virtual void rotate(){}
};
