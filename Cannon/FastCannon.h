#ifndef FASTCANNON_H
#define FASTCANNON_H

#include "ICannon.h"

class FastCannon : public ICannon
{
    
public:
    
    FastCannon(Game *game);
    ~FastCannon();
    
    virtual void draw() override;
    virtual void fire() override;
};

#endif // FASTCANNON_H
