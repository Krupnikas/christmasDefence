#pragma once

#include <Cannon/ICannon.h>

class CSlowCannon : public ICannon
{
private:
    
public:
    
    CSlowCannon();
    ~CSlowCannon();
    
    virtual void fire() override;
};
