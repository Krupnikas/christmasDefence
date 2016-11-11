#ifndef CANNON_H
#define CANNON_H

#include <Game/Resource.h>
#include <Game/Game.h>

class ICannon
{     
    enum CannonType {
        SMALL, MEDIUM, BIG
    };

protected:
    
    double hp;
    double angle;
    double globalRadius;  
    Game *game;
    
public:

    
    virtual ~ICannon();

    virtual void draw();
    virtual void fire();

};

#endif // CANNON_H
