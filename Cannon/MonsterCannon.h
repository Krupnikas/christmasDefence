#pragma once

#include <Cannon/ICannon.h>

class CMonsterCannon : public ICannon
{
private:
    
public:
    
     CMonsterCannon();
     ~CMonsterCannon();
    
    virtual void fire() override;
};
