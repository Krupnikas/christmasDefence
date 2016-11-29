#include <Enemy/FastEnemy.h>
#include <Enemy/CHpBackground.h>
#include <Enemy/CHpCurrent.h>
#include <Game/Game.h>
#include <Game/Helper.h>

CFastEnemy::CFastEnemy(CGame *game)
{
    //IEnemy fields
    movements = std::shared_ptr<mov::Movements>(new mov::Movements(game));
    moveIter = movements->iterNum(FastEnemyStep);
    hpCur = hpMax = FastEnemyHp;
    dead = false;
    
    //IGameObject fields
    angle = movements->curAngle();
    center = movements->curCenter();
    leftTop.setX(center.x() - textureSize.width() / 2);
    leftTop.setY(center.y() - textureSize.height() / 2);
    
    this->game = game;
    zOrder = 2;
    
    textureSize = FastEnemyTextureSize;
    size = FastEnemySize;
    pixmap = &game->r->fast_enemy_2;
    position = game->scene->addPixmap(textureSize, pixmap);
    
    //IEnemy fields
    hpBackgroundItem = std::make_shared<CHpBackground>(this);
    hpCurItem = std::make_shared<CHpCurrent>(this);
}
