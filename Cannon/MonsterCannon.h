#ifndef MONSTERCANNON_H
#define MONSTERCANNON_H

#include "ICannon.h"

class MonsterCannon : public ICannon
{
private:
    
public:
    
     MonsterCannon();
     ~MonsterCannon();
    
    virtual void draw() override;
    virtual void fire() override;
};

#endif // MONSTERCANNON_H
