#include <Game/Game.h>

Game::Game(R *r, Scene *scene) : r(r), scene(scene) {
    cannons.resize(CellNumY);
    for (int i = 0; i < CellNumY; ++i)
        cannons[i].resize(CellNumX);
}

Game::~Game()
{
    
}


