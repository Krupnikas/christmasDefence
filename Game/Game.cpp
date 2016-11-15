#include <Game/Game.h>

Game::Game(R *r, Scene *scene, MainView *view) : r(r), scene(scene), view(view) {
    cannons.resize(CellNumY);
    for (int i = 0; i < CellNumY; ++i)
        cannons[i].resize(CellNumX);
    
    cannons[5][5] = std::static_pointer_cast<ICannon>(
                std::make_shared<FastCannon>(this, 5, 5, 100, 30, 100));
    
    QTimer *timer = new QTimer(this);
    FastCannon *can = reinterpret_cast<FastCannon*>(cannons[5][5].get());
    connect(timer, SIGNAL(timeout()), can, SLOT(rotate()));
    timer->start(1);
    
}

Game::~Game()
{
    
}

void Game::updateObjects()
{
    cannons[5][5]->draw();
}


