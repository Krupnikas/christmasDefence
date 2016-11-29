#include <Game/GameObject.h>
#include <Game/Game.h>

CGameObject::CGameObject(){}

CGameObject::CGameObject(qreal angle, qreal zOrder, QPointF center, QPointF leftTop, QSizeF size, QPixmap *pixmap, CGame *game):
    angle(angle),
    zOrder(zOrder),
    center(center),
    leftTop(leftTop),
    textureSize(size),
    pixmap(pixmap),
    game(game)
{}

CGameObject::~CGameObject(){
    qDebug() <<  label << " deleted";
}

void CGameObject::scaleItem()
{
    if (position)
        game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);
}

void CGameObject::scaleItemWithLoss(QSizeF newSize, ScaleCenter scaleCenter)
{
    game->scene->scaleItem(textureSize, newSize, position, scaleCenter);
}

void CGameObject::draw()
{
    game->scene->positionItem(leftTop, textureSize, angle, zOrder, position);
    //show();
}

void CGameObject::remove()
{
    if (position)
        game->scene->removeItem(position);
}

void CGameObject::hide()
{
    position->hide();
    position->setFlag(QGraphicsItem::ItemHasNoContents, true);
}

void CGameObject::show()
{
    position->setFlag(QGraphicsItem::ItemHasNoContents, false);
    position->show();
}

bool CGameObject::isVisible()
{
    return position->isVisible();
}

QPointF CGameObject::getCenter() const
{
    return center;
}

void CGameObject::setCenter(const QPointF &value)
{
    center = value;
}

qreal CGameObject::getAngle() const
{
    return angle;
}

void CGameObject::setAngle(const qreal &value)
{
    angle = value;
}

std::shared_ptr<QGraphicsItem> CGameObject::getPosition() const
{
    return position;
}

qreal CGameObject::getZOrder() const
{
    return zOrder;
}

void CGameObject::setZOrder(const qreal &value)
{
    zOrder = value;
    position->setZValue(value);
}

QSizeF CGameObject::getTextureSize() const
{
    return textureSize;
}

QSizeF CGameObject::getSize() const
{
    return size;
}

QPointF CGameObject::getLeftTop() const
{
    return leftTop;
}

void CGameObject::setLeftTop(const QPointF &value)
{
    leftTop = value;
}

QPixmap *CGameObject::getPixmap() const
{
    return pixmap;
}

CGame *CGameObject::getGame() const
{
    return game;
}

void CGameObject::setTextureSize(const QSizeF &value)
{
    textureSize = value;
}

void CGameObject::setSize(const QSizeF &value)
{
    size = value;
}


