#ifndef GAME_H
#define GAME_H
//#define TEST

#include <Game/Scene.h>
#include <Game/resource.h>

class Game 
{
    
public:

    QGraphicsScene *gameScene; //Всё действо будет происходить на этой сцене
    
    R *r;
    Scene *scene;
    
    Game(R *r_in, Scene *scene);
    ~Game();
    
};


#endif // GAME_H
