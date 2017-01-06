#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <SceneObject/Button.h>
#include <Cannon/BurnCannon.h>
#include <Cannon/FastCannon.h>
#include <Cannon/MonsterCannon.h>
#include <Cannon/SlowCannon.h>

class CCannonSelection : public IInfoBlock
{
    Q_OBJECT
    
public:

    std::vector<std::shared_ptr<CButton>> cannonButton;
    std::shared_ptr<CButton> closeButton;

    qreal backgroundImageSize;

    QPoint selectedCell;

    CCannonSelection(CGame *game, QPoint SelectedCell);
    ~CCannonSelection();

    void updatePosition(QPoint SelectedCell);
    void initButtons();
    void updateButtonsPositions();

    QPoint calculateTopLeftForButton(int i);
    int getCannonPrice(int i);
    
    virtual void show();
    virtual void hide();
    virtual void draw();

private slots:
    void onButtonPressed(eButtonType Type);
    void onCashChanged(int newCash);
};
