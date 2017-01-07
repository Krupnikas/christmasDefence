#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <InfoBlock/ImageAndNumber.h>

class CUserInfo : public IInfoBlock
{
    Q_OBJECT
public:
    CUserInfo(CGame *game);

    const int INTERNAL_OFFSET_X = 15;
    const int INTERNAL_OFFSET_Y = 15;

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


