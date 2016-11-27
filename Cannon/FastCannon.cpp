#include <mainview.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastCannon::CFastCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    this->angle = angle;
    this->game = game;
    this->zOrder = 2;
    
    this->size = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_cannon_2;
    position = game->scene->addPixmap(size, pixmap);
    
    this->leftTop = game->cellLeftTop(cell);
    this->center = game->cellCenter(cell);
    
    //ICannon fields
    this->gameCell = cell;
    this->rotationSpeed = FastCannonRotation;
    this->fireSpeed = FastCannonInterval;
    this->globalRadius = FastCannonRadius;
    this->radiusItem = game->scene->addEllipse(center, QSizeF(FastCannonRadius * 2, FastCannonRadius * 2));
}

CFastCannon::~CFastCannon(){}

void CFastCannon::fire(qreal angle)
{
    std::shared_ptr<IBullet> bullet = std::make_shared<CFastBullet>(game, center, angle);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
    //connect(game->gameTimer, SIGNAL(timeout()), bullet.get(), SLOT(onTimer()));
}
