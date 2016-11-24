#include <Enemy/FastEnemy.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastEnemy::CFastEnemy(CGame *game)
{
    //IEnemy fields
    this->movements = std::make_shared<Movements>(game);
    
    //IGameObject fields
    this->angle = movements->curAngle();
    this->center = movements->curCenter();
    this->leftTop.setX(center.x() - size.width() / 2);
    this->leftTop.setY(center.y() - size.height() / 2);
    
    this->game = game;
    this->zOrder = 2;
    
    this->size = QSize(CellSize, CellSize);
    this->pixmap = &game->r->fast_enemy_2;
    this->position = game->scene->addPixmap(size, pixmap);
    

}

bool CFastEnemy::move()
{
    center = movements->move();
    angle = movements->curAngle();
    game->scene->positionItemByCenter(center, size, angle, zOrder, position);
    return game->scene->insideGameRect(center);
}
