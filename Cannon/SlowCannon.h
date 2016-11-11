#ifndef SLOWCANNON_H
#define SLOWCANNON_H

#include <Cannon/ICannon.h>

class SlowCannon : public ICannon
{
private:
    
public:
    
    SlowCannon();
    ~SlowCannon();
    
    virtual void draw() override;
    virtual void fire() override;
};

#endif // SLOWCANNON_H
