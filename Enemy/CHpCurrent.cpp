#include <Enemy/IEnemy.h>
#include <Enemy/CHpCurrent.h>
#include <Game/Game.h>

CHpCurrent::CHpCurrent(IEnemy *enemy)
{
    //IGameObject fields
    this->game = enemy->getGame();
    
    angle = 0;
    center = enemy->getCenter();
    leftTop.setX(center.x() - HpSize.width() / 2);
    leftTop.setY(enemy->getLeftTop().y() + game->CellSize - HpSize.height());
    
    zOrder = enemy->getZOrder() + 0.2;
    
    textureSize = HpSize;
    size = HpSize;
    pixmap = game->r->hp_cur;
    position = game->scene->addPixmap(textureSize, pixmap);
}
