#include "Game.h"
#include <Cannon/FastCannon.h>

Game::Game(R *r_in) : r(r_in)
{
    gameScene = new QGraphicsScene();
}

Game::~Game()
{
    
}


