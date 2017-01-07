#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <SceneObject/Button.h>
#include <Cannon/ICannon.h>

class CCannonUpgrade : public IInfoBlock
{
      Q_OBJECT
public:
    CCannonUpgrade(CGame *game, QPoint SelectedCell);


    std::shared_ptr<CButton> upgradeButton;
    std::shared_ptr<CButton> sellButton;
    std::shared_ptr<CButton> closeButton;

    qreal backgroundImageSize;
    QPoint selectedCell;

    void updatePosition(QPoint SelectedCell);
    void initButtons();
    void updateButtonsPositions();

    virtual void show();
    virtual void hide();
    virtual void draw();

private slots:
    void onButtonPressed(int type);
};

