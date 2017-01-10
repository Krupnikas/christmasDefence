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

    std::shared_ptr<CSceneObject> cellSelection;
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
    
    virtual void scale() override;
    virtual void scaleWithLoss(QSizeF newSize) override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

private slots:
    void onButtonPressed(int type);
    void onCashChanged(int newCash);
};
