#include <SceneObject/Button.h>
#include <Helper.h>
#include <mainview.h>

CButton::CButton(qreal zOrder, QPointF center, QSizeF size,
                 QPixmap *normalPixmap, QPixmap *focusedPixmap, QPixmap *pressedPixmap,
                 CGame *game, eButtonType type):
    type(type),
    mouseDown(false)
{
    this->zOrder = zOrder;
    
    this->center = center;
    this->leftTop = center - QPointF(size.width() / 2, size.height() / 2);
    this->textureSize = this->size = size;
    this->game = game;
    
    normalItem = std::make_shared<CSceneObject>(
                0, zOrder,
                leftTop, size,
                normalPixmap, game);
    
    focusedItem = std::make_shared<CSceneObject>(
                0, zOrder,
                leftTop, size,
                focusedPixmap, game);
    
    pressedItem = std::make_shared<CSceneObject>(
                0, zOrder,
                leftTop, size,
                pressedPixmap, game);
    

}

void CButton::scale()
{
    normalItem->scale();
    focusedItem->scale();
    pressedItem->scale();    
}

void CButton::scaleWithLoss(QSizeF newSize)
{
    normalItem->scaleWithLoss(newSize);
    focusedItem->scaleWithLoss(newSize);
    pressedItem->scaleWithLoss(newSize);    
}

void CButton::remove()
{
    normalItem->remove();
    focusedItem->remove();
    pressedItem->remove();    
}

void CButton::draw()
{
    normalItem->draw();
    focusedItem->draw();
    pressedItem->draw();}

void CButton::hide()
{
    normalItem->hide();
    focusedItem->hide();
    pressedItem->hide();
    game->view->disconnect(this);
}

void CButton::show()
{
    normalItem->show();
    focusedItem->hide();
    pressedItem->hide();
    mouseDown = false;
    
    connect(game->view, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(game->view, SIGNAL(mouseDown(QMouseEvent*)), this, SLOT(onMouseDown(QMouseEvent*)));
    connect(game->view, SIGNAL(mouseUp(QMouseEvent*)), this, SLOT(onMouseUp(QMouseEvent*)));
}

bool CButton::isVisible()
{
    return normalItem->isVisible() || focusedItem->isVisible() || pressedItem->isVisible();
}

void CButton::setCenter(const QPointF &value)
{
    CSceneObject::setCenter(value);
    normalItem->setCenter(value);
    focusedItem->setCenter(value);;
    pressedItem->setCenter(value);;
}

void CButton::setAngle(const qreal &value)
{
    CSceneObject::setAngle(value);
    normalItem->setAngle(value);
    focusedItem->setAngle(value);
    pressedItem->setAngle(value);;
}

void CButton::setZOrder(const qreal &value)
{
    CSceneObject::setZOrder(value);
    normalItem->setZOrder(value);
    focusedItem->setZOrder(value);
    pressedItem->setZOrder(value);
}

void CButton::setTextureSize(const QSizeF &value)
{
    CSceneObject::setTextureSize(value);
    normalItem->setTextureSize(value);
    focusedItem->setTextureSize(value);;
    pressedItem->setTextureSize(value);;
}

void CButton::setSize(const QSizeF &value)
{
    CSceneObject::setSize(value);
    normalItem->setSize(value);
    focusedItem->setSize(value);
    pressedItem->setSize(value);
}

void CButton::setLeftTop(const QPointF &value)
{
    CSceneObject::setLeftTop(value);
    normalItem->setLeftTop(value);
    focusedItem->setLeftTop(value);;
    pressedItem->setLeftTop(value);
}

void CButton::onMouseMove(QMouseEvent *event)
{
    QPointF p(game->scene->toLocalPoint(event->localPos()));
    
    if (!isVisible())
        return;
    
    if (!mouseDown)
    {
        if (checkInside(p))
        {
            normalItem->hide();
            pressedItem->hide();
            focusedItem->show();
        }
        else
        {
            focusedItem->hide();
            pressedItem->hide();
            normalItem->show();
        }
    }
}

void CButton::onMouseDown(QMouseEvent *event)
{
    QPointF p(game->scene->toLocalPoint(event->localPos()));
    
    if (!isVisible() || !checkInside(p))
        return;
    
    mouseDown = true;
    normalItem->hide();
    focusedItem->hide();
    pressedItem->show();
}

void CButton::onMouseUp(QMouseEvent *event)
{
    QPointF p(game->scene->toLocalPoint(event->localPos()));
    
    if (!isVisible())
        return;
    
    if (mouseDown)
    {
        mouseDown = false;

        if (checkInside(p))
        {
            normalItem->hide();
            pressedItem->hide();
            focusedItem->show();
            emit pressed(type);
        }
        else
        {
            focusedItem->hide();
            pressedItem->hide();
            normalItem->show();
        }
    }
}

CButton::checkInside(QPointF p)
{
    QRectF buttonRect(leftTop, size);
    return buttonRect.contains(p);
}
