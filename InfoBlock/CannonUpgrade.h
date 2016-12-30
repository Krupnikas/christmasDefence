#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <SceneObject/Button.h>
#include <Cannon/ICannon.h>

class CCannonUpgrade : public IInfoBlock
{
      Q_OBJECT
public:
    CCannonUpgrade(CGame *game, QPoint selectedCell);


    std::shared_ptr<CButton> upgradeButton;
    std::shared_ptr<CButton> sellButton;
    std::shared_ptr<CButton> closeButton;

    qreal backgroundImageSize;

    void updatePosition(QPoint selectedCell);
    void initButtons();
    void updateButtonsPositions();

    virtual void show();
    virtual void hide();
    virtual void draw();

private slots:
    void onButtonPressed(eButtonType Type);
};

