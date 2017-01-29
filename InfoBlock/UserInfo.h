#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <InfoBlock/ImageAndNumber.h>

class CUserInfo : public IInfoBlock
{
    Q_OBJECT
public:
    CUserInfo(CGame *game);

    const qreal InternalPercentageOffsetX = 5;
    const qreal InternalPercentageOffsetY = 1;

    std::shared_ptr<CImageAndNumber> hp;
    std::shared_ptr<CImageAndNumber> coins;

    virtual void scale() override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

public slots:
    void onHpChanged(int newHp);
    void onCashChanged(int newCash);
};


