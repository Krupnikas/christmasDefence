#include "CannonUpgrade.h"

CCannonUpgrade::CCannonUpgrade(CGame *game, QPoint selectedCell)
{
    //IGameObject fields
    this->label = "Cannon Upgrade Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = 5;

    backgroundImageSize = CannonUpgradeRadius * 8.0 / 3;

    this->textureSize = QSize(backgroundImageSize,
                              backgroundImageSize);
    this->pixmap = &game->r->cannonUpgradeBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->center = game->cellCenter(selectedCell);

    initButtons();
    updatePosition(selectedCell);
}

void CCannonUpgrade::updatePosition(QPoint selectedCell)
{
    center = game->cellCenter(selectedCell);
    setLeftTop(center - QPointF(backgroundImageSize/2,
                                backgroundImageSize/2));
    updateButtonsPositions();
}

void CCannonUpgrade::initButtons()
{
    if (CloseButtonInInfoBlocksEnabled)
    {
        closeButton.init(eBTCloseButton,
                         QRect(center.x() - CannonUpgradeButtonSize/2,
                               center.y() + CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                               CannonUpgradeButtonSize,
                               CannonUpgradeButtonSize),
                         &game->r->buttonClose,
                         game,
                         ButtonZOrder,
                         0);

        connect(&closeButton, SIGNAL(pressed(eButtonTypes)),
                this, SLOT(onButtonPressed(eButtonTypes)));
    }

    upgradeButton.init(eBTcannonUpgrade,
                     QRect(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                           center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                           CannonUpgradeButtonSize,
                           CannonUpgradeButtonSize),
                     &game->r->buttonUpgrade,
                     game,
                     ButtonZOrder,
                     0);

    connect(&upgradeButton, SIGNAL(pressed(eButtonTypes)),
            this, SLOT(onButtonPressed(eButtonTypes)));

    sellButton.init(eBTcannonSell,
                     QRect(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                           center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                           CannonUpgradeButtonSize,
                           CannonUpgradeButtonSize),
                     &game->r->buttonSell,
                     game,
                     ButtonZOrder,
                     0);

    connect(&sellButton, SIGNAL(pressed(eButtonTypes)),
            this, SLOT(onButtonPressed(eButtonTypes)));
}

void CCannonUpgrade::updateButtonsPositions()
{
    if (CloseButtonInInfoBlocksEnabled)
    {
        closeButton.setLeftTop(QPointF(center.x() - CannonUpgradeButtonSize/2,
                                      center.y() + CannonUpgradeRadius - CannonUpgradeButtonSize/2));
        closeButton.draw();
    }

    upgradeButton.setLeftTop(QPointF(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                     center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    upgradeButton.draw();

    sellButton.setLeftTop(QPointF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    sellButton.draw();
}

void CCannonUpgrade::show()
{
    CGameObject::show();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton.show();

    upgradeButton.show();
    sellButton.show();
}

void CCannonUpgrade::hide()
{
    CGameObject::hide();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton.hide();

    upgradeButton.hide();
    sellButton.hide();
}

void CCannonUpgrade::draw()
{
    CGameObject::draw();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton.draw();

    upgradeButton.draw();
    sellButton.draw();
}

void CCannonUpgrade::onButtonPressed(eButtonTypes Type)
{
    switch (Type){
    case eBTCloseButton:
        break;
    case eBTcannonUpgrade:
        game->cannons[game->selectedCell.x()][game->selectedCell.y()]->upgrade();
        break;
    case eBTcannonSell:
        game->cannons[game->selectedCell.x()][game->selectedCell.y()]->sell();
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << Type;
    }
    game->deselectCell();
}
