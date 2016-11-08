#ifndef GAME_H
#define GAME_H
//#define TEST

#include <QGraphicsScene>
#include <Game/resource.h>

class Game 
{
    
public:

    QGraphicsScene *gameScene; //Всё действо будет происходить на этой сцене

    R *r;
    Game(R *r_in);
    ~Game();
    
};


#endif // GAME_H
