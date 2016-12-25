#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Game/Button.h>
#include <Cannon/ICannon.h>

class CCannonUpgrade : public IInfoBlock
{
      Q_OBJECT
public:
    CCannonUpgrade(CGame *game, QPoint selectedCell);


    CButton upgradeButton;
    CButton sellButton;
    CButton closeButton;

    qreal backgroundImageSize;

    void updatePosition(QPoint selectedCell);
    void initButtons();
    void updateButtonsPositions();

    virtual void show();
    virtual void hide();
    virtual void draw();

private slots:
    void onButtonPressed(eButtonTypes Type);
};

