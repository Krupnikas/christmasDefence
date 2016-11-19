#pragma once

#include <Cannon/ICannon.h>

class CMonsterCannon : public ICannon
{
private:
    
public:
    
     CMonsterCannon();
     ~CMonsterCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
     
public slots:
    virtual void onTimer(){}
};
