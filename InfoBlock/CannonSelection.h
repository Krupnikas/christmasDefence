#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Game/Button.h>

class CCannonSelection : public IInfoBlock
{
    Q_OBJECT
    
public:

    CButton cannonButton[TypesOfCannon];
    CButton closeButton;

    qreal backgroundImageSize;

    CCannonSelection(CGame *game, QPoint selectedCell);
    ~CCannonSelection();

    void updatePosition(QPoint selectedCell);
    void initButtons();
    void updateButtonsPositions();
    
    void show();
    void hide();

private slots:
    void onCloseButtonPressed();
};
