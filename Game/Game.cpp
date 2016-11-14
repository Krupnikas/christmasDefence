#include <Game/Game.h>

Game::Game(R *r, Scene *scene) : r(r), scene(scene) {
    cannons.resize(CellNumY);
    for (int i = 0; i < CellNumY; ++i)
        cannons[i].resize(CellNumX);
    
    cannons[0][0] = std::static_pointer_cast<ICannon>(
                std::make_shared<FastCannon>(this, 0, 0, 100, 30, 100));

    QTimer *timer = new QTimer(this);
    FastCannon *can = reinterpret_cast<FastCannon*>(cannons[0][0].get());
    connect(timer, SIGNAL(timeout()), can, SLOT(rotate()));
    timer->start(200);
    
}

Game::~Game()
{
    
}

void Game::updateObjects()
{
    cannons[0][0]->draw();
}


