#include <Game/Game.h>

Game::Game(R *r, Scene *scene, MainView *view) : r(r), scene(scene), view(view) {
    cannons.resize(CellNumY);
    for (int i = 0; i < CellNumY; ++i)
        cannons[i].resize(CellNumX);
    
    cannons[5][5] = std::static_pointer_cast<ICannon>(
                std::make_shared<FastCannon>(this, 5, 5, 100, 30, 100));

    cannons[2][2] = std::static_pointer_cast<ICannon>(
                std::make_shared<FastCannon>(this, 2, 2, 100, 30, 100));
    
    QLineF line(1, 1, 1, 2);
    line.translate(2, 2);
    
    gameTimer = new QTimer(this);
    FastCannon *can = reinterpret_cast<FastCannon*>(cannons[5][5].get());
    FastCannon *can2 = reinterpret_cast<FastCannon*>(cannons[2][2].get());
    connect(gameTimer, SIGNAL(timeout()), can2, SLOT(rotate()));
    connect(gameTimer, SIGNAL(timeout()), can, SLOT(rotate()));
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateObjects()));
    gameTimer->start(16);
    
}

Game::~Game()
{
    
}

void Game::updateObjects()
{
    for (size_t i = 0; i < bullets.size(); ++i)
        if (scene->insideGameRect(bullets[i]->getCenter()))
        {
            bullets[i]->move();
            bullets[i]->draw();
        }
    
    for (int i = 0; i < CellNumY; ++i)
        for (int j = 0; j < CellNumX; ++j)
            if (cannons[i][j])
                cannons[i][j]->draw();
}


