#include <Enemy/IEnemy.h>
#include <Enemy/CHpCurrent.h>
#include <Game/Game.h>

CHpCurrent::CHpCurrent(IEnemy *enemy)
{
    //IGameObject fields
    this->game = enemy->getGame();
    
    angle = 0;
    center = enemy->getCenter();
    leftTop.setX(center.x() - m::HpSize.width() / 2);
    leftTop.setY(enemy->getLeftTop().y() + m::CellSize - m::HpSize.height());
    
    zOrder = enemy->getZOrder() + 0.2;
    
    textureSize = m::HpSize;
    size = m::HpSize;
    pixmap = game->r->hp_cur;
    position = game->scene->addPixmap(textureSize, pixmap);
}
