#pragma once

#include <Game/Resource.h>
#include <Game/Game.h>

class ICannon
{     
    enum CannonType {
        SMALL, MEDIUM, BIG
    };

protected:
    
    int x;
    int y;
    
    double hp;
    double angle;
    double globalRadius;  
    Game *game;
    
public:

    
    virtual ~ICannon();

    virtual void draw();
    virtual void fire();

};
