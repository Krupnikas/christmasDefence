#include <mainview.h>
#include <Cannon/FastCannon.h>
#include <Bullet/FastBullet.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastCannon::CFastCannon(CGame *game, QPoint cell, double angle)
{
    //IGameObject fields
    this->label = "Fast Cannon";
    this->angle = angle;
    this->game = game;
    this->zOrder = 2;
    
    this->textureSize = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_cannon_1;
    position = game->scene->addPixmap(textureSize, pixmap);
    
    this->leftTop = game->cellLeftTop(cell);
    this->center = game->cellCenter(cell);
    
    //ICannon fields
    this->sizeType = SMALL;
    this->gameCell = cell;
    this->rotationSpeed = FastCannonSmRotation;
    this->fireSpeed = FastCannonSmFireSpeed;
    this->fireRadius = FastCannonSmRadius;
    this->radiusItem = game->scene->addPixmap(QSizeF(2 * fireRadius,
                                                     2 * fireRadius),
                                                     &game->r->entireRadius);
    hideRadius();
}

CFastCannon::~CFastCannon(){}

void CFastCannon::fire()
{
    std::shared_ptr<IBullet> bullet = 
            std::make_shared<CFastBullet>(game, center, this->angle, sizeType);
    game->bullets.push_back(bullet);
    bullet->draw();
    bullet->show();
}

void CFastCannon::upgrade()
{
    ICannon::upgrade();
    
    this->pixmap = 
            helper::choose(
                            sizeType, 
                            &game->r->fast_cannon_1, 
                            &game->r->fast_cannon_2, 
                            &game->r->fast_cannon_3);
                
    game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);
    
    
    rotationSpeed = 
            helper::choose(sizeType, 
                            FastCannonSmRotation,
                            FastCannonMidRotation,
                            FastCannonBigRotation);
    fireSpeed = 
            helper::choose(sizeType,
                            FastCannonSmFireSpeed,
                            FastCannonMidFireSpeed,
                            FastCannonBigFireSpeed);
    fireRadius = 
            helper::choose(sizeType,
                            FastCannonSmRadius,
                            FastCannonMidRadius,
                            FastCannonBigRadius);
    game->scene->removeItem(radiusItem);
    radiusItem = game->scene->addPixmap(QSizeF(2 * fireRadius,
                                                     2 * fireRadius),
                                                     &game->r->entireRadius);
    game->deselectCell();
    game->selectCell(gameCell);
    draw();
    show();
}
