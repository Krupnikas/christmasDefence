#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Helper.h>

class CImageAndNumber : public IInfoBlock
{
public:
    CImageAndNumber(CGame *game, QPixmap *IconPixmap, QRect BoundingRect);

    const int ICON_X_OFFSET = 20;
    const int ICON_Y_OFFSET = 25;
    const int TEXT_X_OFFSET = 2;
    const int TEXT_Y_OFFSET = 25;

    void updatePosition(QRect BoundingRect);

    std::shared_ptr<QPixmap> renderedText;
    std::shared_ptr<CSceneObject> icon;
    std::shared_ptr<CSceneObject> text;

    void changeText(QString newText);

    virtual void draw();
    virtual void show();
    virtual void scaleItem();
};

