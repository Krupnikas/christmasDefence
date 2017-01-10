#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <SceneObject/Button.h>
#include <Cannon/ICannon.h>

class CCannonUpgrade : public IInfoBlock
{
      Q_OBJECT
public:
    CCannonUpgrade(CGame *game, QPoint SelectedCell);

    void updatePosition(QPoint SelectedCell);
    void initButtons();
    void updateButtonsPositions();

    virtual void scale() override;
    virtual void scaleWithLoss(QSizeF newSize) override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

private slots:
    void onButtonPressed(int type);
    
private:
    std::shared_ptr<CButton> upgradeButton;
    std::shared_ptr<CButton> sellButton;
    std::shared_ptr<CButton> closeButton;

    qreal backgroundImageSize;
    QPoint selectedCell;
};

