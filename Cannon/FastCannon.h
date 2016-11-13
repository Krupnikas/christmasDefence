#ifndef FASTCANNON_H
#define FASTCANNON_H

#include <Cannon/ICannon.h>

class FastCannon : public ICannon
{
    
public:
    
    FastCannon(Game *game, int x, int y);
    ~FastCannon();
    
    virtual void draw() override;
    virtual void fire() override;
};

#endif // FASTCANNON_H
