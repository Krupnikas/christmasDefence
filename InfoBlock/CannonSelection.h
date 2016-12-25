#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Game/Button.h>
#include <Cannon/BurnCannon.h>
#include <Cannon/FastCannon.h>
#include <Cannon/MonsterCannon.h>
#include <Cannon/SlowCannon.h>

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

    QPoint calculateTopLeftForButton(int i);
    
    virtual void show();
    virtual void hide();
    virtual void draw();

private slots:
    void onButtonPressed(eButtonTypes Type);
};
