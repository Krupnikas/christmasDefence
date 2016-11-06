#ifndef BURNCANNON_H
#define BURNCANNON_H

#include "ICannon.h"

class BurnCannon : public ICannon
{
private:
    
public:
    
    BurnCannon();
    ~BurnCannon();
    
    virtual void draw() override;
    virtual void fire() override;
};

#endif // BURNCANNON_H
