#include <Game/Game.h>
#include <Cannon/ICannon.h>
#include <Cannon/CannonRadius.h>

CCannonRadius::CCannonRadius(ICannon *cannon)
{
    //IGameObject fields
    label = "Cannon radius";
    angle = 0;
    game = cannon->getGame();
    zOrder = cannon->getZOrder() - 0.1;
    
    size = textureSize = QSizeF(cannon->getFireRadius() * 2, cannon->getFireRadius() * 2);
    pixmap = &game->r->entireRadius;
    position = game->scene->addPixmap(textureSize, pixmap);
    
    center = cannon->getCenter();
    leftTop = QPointF(center.x() - textureSize.width() / 2, center.y() - textureSize.height() / 2);
}

void CCannonRadius::upgrade(ICannon *cannon)
{
    remove();
    this->textureSize = QSizeF(cannon->getFireRadius() * 2, cannon->getFireRadius() * 2);
    leftTop = QPointF(center.x() - textureSize.width() / 2, center.y() - textureSize.height() / 2);
    scale();
}
