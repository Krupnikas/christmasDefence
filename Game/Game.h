#pragma once

#include <Game/Resource.h>
#include <Game/Scene.h>
#include <Bullet/IBullet.h>

class ICannon;

class Game 
{
    
//public attributes
public:
    R *r;
    Scene *scene;

//private attributes
private:
    std::vector<std::vector<IBullet> > bullets;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    
    
//public methods
public:
    Game(R *r, Scene *scene);
    ~Game();

    
};

