#include <Enemy/FastEnemy.h>
#include <Enemy/CHpBackground.h>
#include <Enemy/CHpCurrent.h>
#include <Game/Game.h>
#include <Helper.h>

CFastEnemy::CFastEnemy(CGame *game, int enemyTexture, int enemyPower)
{
    //IEnemy fields
    movements = std::shared_ptr<mov::Movements>(new mov::Movements(game));
    moveIter = movements->iterNum(m::FastEnemyStep);
    hpCur = hpMax = enemyPower * m::EnemyHpFactor;
    
    //IGameObject fields
    label = "Fast Enemy";
    angle = movements->curAngle();
    center = movements->curCenter();
    leftTop.setX(center.x() - textureSize.width() / 2);
    leftTop.setY(center.y() - textureSize.height() / 2);
    
    this->game = game;
    zOrder = m::EnemyZOrder;
    
    textureSize = m::FastEnemyTextureSize;
    size = m::FastEnemySize;
    pixmap = getTexture(enemyTexture);
    position = game->scene->addPixmap(textureSize, pixmap);
    
    //IEnemy fields
    hpBackgroundItem = std::make_shared<CHpBackground>(this);
    hpCurItem = std::make_shared<CHpCurrent>(this);
}

std::shared_ptr<QPixmap> CFastEnemy::getTexture(int enemyTexture)
{
    switch (enemyTexture)
    {
    case 1:
        return game->r->fast_enemy_1;
    case 2:
        return game->r->fast_enemy_2;
    case 3:
        return game->r->fast_enemy_3;
    default:
        qDebug() << "incorrect enemy texture";
        return game->r->fast_enemy_2;
    }
}
