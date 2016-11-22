#include <Game/IGameObject.h>
#include <Game/Game.h>

IGameObject::IGameObject(){}
IGameObject::~IGameObject(){}

void IGameObject::scaleItem()
{
    if (position)
        game->scene->removeItem(position);
    position = game->scene->addPixmap(size, pixmap);
}

void IGameObject::draw()
{
    game->scene->positionItem(leftTop, size, angle, zOrder, position);
}

void IGameObject::hide()
{
    if (position)
    game->scene->removeItem(position);
}

QPointF IGameObject::getCenter() const
{
    return center;
}

void IGameObject::setCenter(const QPointF &value)
{
    center = value;
}

qreal IGameObject::getAngle() const
{
    return angle;
}

void IGameObject::setAngle(const qreal &value)
{
    angle = value;
}
