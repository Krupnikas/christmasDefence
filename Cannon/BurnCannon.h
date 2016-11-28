#pragma once

#include <Cannon/ICannon.h>

class CBurnCannon : public ICannon
{
public:
    
    CBurnCannon();
    
    virtual ~CBurnCannon();
    
    virtual void fire() override;
    
public slots:
    virtual void onTimer(){}
};
