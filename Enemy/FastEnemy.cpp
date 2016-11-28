#include <Enemy/FastEnemy.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastEnemy::CFastEnemy(CGame *game)
{
    //IEnemy fields
    this->movements = std::shared_ptr<mov::Movements>(new mov::Movements(game));
    this->moveIter = movements->iterNum(FastEnemyStep);
    this->hp = FastEnemyHp;
    this->dead = false;
    
    //IGameObject fields
    this->angle = movements->curAngle();
    this->center = movements->curCenter();
    this->leftTop.setX(center.x() - textureSize.width() / 2);
    this->leftTop.setY(center.y() - textureSize.height() / 2);
    
    this->game = game;
    this->zOrder = 2;
    
    this->textureSize = FastEnemyTextureSize;
    this->size = FastEnemySize;
    this->pixmap = &game->r->fast_enemy_2;
    this->position = game->scene->addPixmap(textureSize, pixmap);
    

}

bool CFastEnemy::move()
{
    for (int i = 0; i < moveIter; ++i)
        center = movements->move();
    angle = movements->curAngle();
    game->scene->positionItemByCenter(center, textureSize, angle, zOrder, position);
    return game->scene->insideGameRect(center);
}



void CFastEnemy::updateDistances()
{
    movements->updateNext();
}
