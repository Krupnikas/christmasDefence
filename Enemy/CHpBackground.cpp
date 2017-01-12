#include <Enemy/IEnemy.h>
#include <Enemy/CHpBackground.h>
#include <Game/Game.h>

CHpBackground::CHpBackground(IEnemy *enemy)
{
    //IGameObject fields
    this->game = enemy->getGame();
    
    angle = 0;
    center = enemy->getCenter();
    leftTop.setX(center.x() - HpSize.width() / 2);
    leftTop.setY(enemy->getLeftTop().y() + game->CellSize - HpSize.height());
    
    zOrder = enemy->getZOrder() + 0.1;
    
    textureSize = HpSize;
    size = HpSize;
    pixmap = std::shared_ptr<QPixmap>(game->r->hp_background);
    position = game->scene->addPixmap(textureSize, pixmap);
}
