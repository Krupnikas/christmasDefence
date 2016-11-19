#pragma once

#include <Cannon/ICannon.h>

class CBurnCannon : public ICannon
{
private:
    
public:
    
    CBurnCannon();
    
    virtual ~CBurnCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
    
public slots:
    virtual void rotate(){}
};
