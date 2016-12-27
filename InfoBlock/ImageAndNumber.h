#pragma once

#include <InfoBlock/IInfoBlock.h>

class CImageAndNumber : public IInfoBlock
{
public:
    CImageAndNumber(CGame *game, QPixmap *IconPixmap, QRect BoundingRect);

    const int ICON_X_OFFSET = 20;
    const int ICON_Y_OFFSET = 20;

    void updatePosition(QRect BoundingRect);

    virtual void draw();
    virtual void show();
    virtual void scaleItem();

    std::shared_ptr<CGameObject> icon;
};

