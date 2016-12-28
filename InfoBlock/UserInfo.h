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

    virtual void draw();
    virtual void show();
    virtual void scale();

public slots:
    void onHpChanged(int newHp);
    void onCashChanged(int newCash);
};


