#include "ImageAndNumber.h"

CImageAndNumber::CImageAndNumber(CGame *game, QPixmap *IconPixmap, QRect BoundingRect)
{
    //IGameObject fields
    this->label = "Image and number block";
    this->angle = 0;
    this->game = game;
    this->zOrder = 4.5;

    this->textureSize = QSize(BoundingRect.width(),
                              BoundingRect.height());

    this->pixmap = &game->r->imageAndNumberBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);
    this->leftTop = BoundingRect.topLeft();

    icon = std::make_shared<CGameObject>(0, 4.6, QPointF(0,0),
                                         QPointF(leftTop) + QPointF(ICON_X_OFFSET,
                                                                    ICON_Y_OFFSET),
                                         QSizeF(BoundingRect.width() - 2 * ICON_X_OFFSET,
                                                BoundingRect.width() - 2 * ICON_X_OFFSET),
                                         IconPixmap,
                                         game);
}

void CImageAndNumber::updatePosition(QRect BoundingRect)
{
    this->textureSize = QSize(BoundingRect.width(),
                              BoundingRect.height());
    this->leftTop = BoundingRect.topLeft();
}

void CImageAndNumber::draw()
{
    CGameObject::draw();
    icon->draw();
}

void CImageAndNumber::show()
{
    CGameObject::show();
    icon->show();
}

void CImageAndNumber::scaleItem()
{
    CGameObject::scaleItem();
    icon->scaleItem();
}

