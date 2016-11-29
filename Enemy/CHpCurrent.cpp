#include <Enemy/IEnemy.h>
#include <Enemy/CHpCurrent.h>
#include <Game/Game.h>

CHpCurrent::CHpCurrent(IEnemy *enemy)
{
    //IGameObject fields
    angle = 0;
    center = enemy->getCenter();
    leftTop.setX(center.x() - HpSize.width() / 2);
    leftTop.setY(enemy->getLeftTop().y() + CellSize - HpSize.height());
    
    this->game = enemy->getGame();
    zOrder = enemy->getZOrder() + 0.2;
    
    textureSize = HpSize;
    size = HpSize;
    pixmap = &game->r->hp_cur;
    position = game->scene->addPixmap(textureSize, pixmap);
}
