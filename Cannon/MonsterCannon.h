#ifndef MONSTERCANNON_H
#define MONSTERCANNON_H

#include <Cannon/ICannon.h>

class MonsterCannon : public ICannon
{
private:
    
public:
    
     MonsterCannon();
     ~MonsterCannon();
    
    virtual void draw() override;
    virtual void fire() override;
     
public slots:
    virtual void rotate(){}
};

#endif // MONSTERCANNON_H
