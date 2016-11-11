#ifndef GAME_H
#define GAME_H
//#define TEST

#include <Game/Resource.h>
#include <Game/Scene.h>
#include <Bullet/IBullet.h>

class Game 
{
    
//public attributes
public:
    R *r;
    Scene *scene;

//private attributes
private:
    std::vector<std::vector<IBullet> > bullets;
    
    
//public methods
public:
    Game(R *r, Scene *scene);
    ~Game();

    
};


#endif // GAME_H
