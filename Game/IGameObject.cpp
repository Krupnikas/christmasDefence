#include <Game/IGameObject.h>
#include <Game/Game.h>

IGameObject::IGameObject(){}

IGameObject::IGameObject(qreal angle, qreal zOrder, QPointF center, QPointF leftTop, QSizeF size, QPixmap *pixmap, CGame *game):
    angle(angle),
    zOrder(zOrder),
    center(center),
    leftTop(leftTop),
    size(size),
    pixmap(pixmap),
    game(game)
{}

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
    //show();
}

void IGameObject::remove()
{
    if (position)
        game->scene->removeItem(position);
}

void IGameObject::hide()
{
    position->hide();
    position->setFlag(QGraphicsItem::ItemHasNoContents, true);
}

void IGameObject::show()
{
    position->setFlag(QGraphicsItem::ItemHasNoContents, false);
    position->show();
}

bool IGameObject::isVisible()
{
    return position->isVisible();
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

std::shared_ptr<QGraphicsItem> IGameObject::getPosition() const
{
    return position;
}

qreal IGameObject::getZOrder() const
{
    return zOrder;
}

void IGameObject::setZOrder(const qreal &value)
{
    zOrder = value;
    position->setZValue(value);
}

QSizeF IGameObject::getSize() const
{
    return size;
}
