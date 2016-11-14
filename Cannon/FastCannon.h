#ifndef FASTCANNON_H
#define FASTCANNON_H

#include <Cannon/ICannon.h>

class FastCannon : public ICannon
{
    
public:
    
    FastCannon(Game *game, int x, int y, double hp, double angle, double globalRadius);
    ~FastCannon();
    
    virtual void draw() override;
    virtual void fire() override;
    
    
public slots:
    virtual void rotate();
    
};

#endif // FASTCANNON_H
