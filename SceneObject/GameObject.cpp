#include <SceneObject/SceneObject.h>
#include <Game/Game.h>

CSceneObject::CSceneObject():
    label(""),
    angle(0),
    zOrder(0),
    center(QPointF(0, 0)),
    leftTop(QPointF(0, 0)),
    textureSize(QSizeF(0, 0)),
    size(QSizeF(0, 0)),
    pixmap(nullptr),
    game(nullptr),
    position(nullptr)
{}

CSceneObject::CSceneObject(qreal angle, qreal zOrder, QPointF center, QPointF leftTop, QSizeF size, QPixmap *pixmap, CGame *game):
    angle(angle),
    zOrder(zOrder),
    center(center),
    leftTop(leftTop),
    textureSize(size),
    pixmap(pixmap),
    game(game)
{
    position = game->scene->addPixmap(textureSize, pixmap);
}

CSceneObject::~CSceneObject(){
    //qDebug() <<  label << " deleted";
}

void CSceneObject::scale()
{
    if (position)
        game->scene->removeItem(position);
    position = game->scene->addPixmap(textureSize, pixmap);
}

void CSceneObject::scaleWithLoss(QSizeF newSize)
{
    game->scene->scaleItem(textureSize, newSize, position);
}

void CSceneObject::draw()
{
    game->scene->positionItem(leftTop, textureSize, angle, zOrder, position);
    //show();
}

void CSceneObject::remove()
{
    if (position)
        game->scene->removeItem(position);
}

void CSceneObject::hide()
{
    position->hide();
    position->setFlag(QGraphicsItem::ItemHasNoContents, true);
}

void CSceneObject::show()
{
    position->setFlag(QGraphicsItem::ItemHasNoContents, false);
    position->show();
}

bool CSceneObject::isVisible()
{
    return position->isVisible();
}

QPointF CSceneObject::getCenter() const
{
    return center;
}

void CSceneObject::setCenter(const QPointF &value)
{
    center = value;
}

qreal CSceneObject::getAngle() const
{
    return angle;
}

void CSceneObject::setAngle(const qreal &value)
{
    angle = value;
}

std::shared_ptr<QGraphicsItem> CSceneObject::getPosition() const
{
    return position;
}

qreal CSceneObject::getZOrder() const
{
    return zOrder;
}

void CSceneObject::setZOrder(const qreal &value)
{
    zOrder = value;
    position->setZValue(value);
}

QSizeF CSceneObject::getTextureSize() const
{
    return textureSize;
}

QSizeF CSceneObject::getSize() const
{
    return size;
}

QPointF CSceneObject::getLeftTop() const
{
    return leftTop;
}

void CSceneObject::setLeftTop(const QPointF &value)
{
    leftTop = value;
}

QPixmap *CSceneObject::getPixmap() const
{
    return pixmap;
}

void CSceneObject::setPixmap(QPixmap* Pixmap)
{
    pixmap = Pixmap;
    scale();
}

CGame *CSceneObject::getGame() const
{
    return game;
}

void CSceneObject::setTextureSize(const QSizeF &value)
{
    textureSize = value;
}

void CSceneObject::setSize(const QSizeF &value)
{
    size = value;
}


