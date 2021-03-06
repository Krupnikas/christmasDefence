#include "ImageAndNumber.h"

CImageAndNumber::CImageAndNumber(CGame *game, std::shared_ptr<QPixmap> IconPixmap, QRectF BoundingRect, QString numberText)
{
    //IGameObject fields
    this->label = "Image and number block";
    this->angle = 0;
    this->game = game;
    this->zOrder = 4.5;

    this->textureSize = QSize(BoundingRect.width(),
                              BoundingRect.height());

    this->pixmap = game->r->imageAndNumberBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);
    this->leftTop = BoundingRect.topLeft();

    icon = std::make_shared<CSceneObject>(0, 4.6,
                                          QPointF(leftTop) + QPointF(
                                              BoundingRect.width() * IconPercentOffsetX / 100.0,
                                              BoundingRect.height() * IconPercentOffsetY / 100.0),
                                          QSizeF(BoundingRect.width() - 2 * BoundingRect.width() * IconPercentOffsetX / 100.0,
                                                 BoundingRect.width() - 2 * BoundingRect.width() * IconPercentOffsetX / 100.0),
                                          IconPixmap, game);

    renderedText = helper::renderPixmapFromText(numberText);

    text = std::make_shared<CSceneObject>(0, 4.6,
                                          QPointF(leftTop) +
                                          QPointF(BoundingRect.width() * TextPercentOffsetX / 100.0,
                                                  BoundingRect.height() * IconPercentOffsetY / 100.0
                                                  + BoundingRect.height() * TextPercentOffsetY / 100.0
                                                  + icon->getTextureSize().height()),
                                          QSizeF(BoundingRect.width() - 2 * BoundingRect.width() * TextPercentOffsetX / 100.0,
                                                (BoundingRect.width() - 2 * BoundingRect.width() * TextPercentOffsetX / 100.0)
                                                * renderedText->height() / renderedText->width()),
                                          renderedText, game);
}

void CImageAndNumber::updatePosition(QRect BoundingRect)
{
    this->textureSize = QSize(BoundingRect.width(),
                              BoundingRect.height());
    this->leftTop = BoundingRect.topLeft();
}

void CImageAndNumber::changeText(QString newText)
{
    renderedText = helper::renderPixmapFromText(newText);
    text->setPixmap(renderedText);
    
}

void CImageAndNumber::scale()
{
    CSceneObject::scale();
    icon->scale();
    text->scale();
}

void CImageAndNumber::remove()
{
    icon->remove();
    text->remove();
    CSceneObject::remove();
}

void CImageAndNumber::draw()
{
    CSceneObject::draw();
    icon->draw();
    text->draw();
}

void CImageAndNumber::hide()
{
    CSceneObject::hide();
    icon->hide();
    text->hide();
}

void CImageAndNumber::show()
{
    CSceneObject::show();
    icon->show();
    text->show();
}



