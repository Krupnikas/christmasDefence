#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Helper.h>
#include "math.h"

class CImageAndNumber : public IInfoBlock
{
public:
    CImageAndNumber(CGame *game, std::shared_ptr<QPixmap> IconPixmap, QRectF BoundingRect, QString text = QString("0"));

    const qreal IconPercentOffsetX = 10;
    const qreal IconPercentOffsetY = 15;
    const qreal TextPercentOffsetX = 10;
    const qreal TextPercentOffsetY = 15;

    void updatePosition(QRect BoundingRect);

    std::shared_ptr<QPixmap> renderedText;
    std::shared_ptr<CSceneObject> icon;
    std::shared_ptr<CSceneObject> text;

    void changeText(QString newText);

    virtual void scale() override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;
};

