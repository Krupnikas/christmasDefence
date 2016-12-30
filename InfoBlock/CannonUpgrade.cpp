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
        QRectF rect(center.x() - CannonUpgradeButtonSize/2,
                    center.y() + CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                    CannonUpgradeButtonSize,
                    CannonUpgradeButtonSize);
        closeButton = std::make_shared<CButton>(
                    ButtonZOrder, rect.center(),
                    rect.size(),
                    &game->r->buttonClose, &game->r->buttonClose, &game->r->buttonClose,
                    game, eBTCloseButton);

        connect(closeButton.get(), SIGNAL(pressed(eButtonType)),
                this, SLOT(onButtonPressed(eButtonType)));
    }

    QRectF rect(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                CannonUpgradeButtonSize,
                CannonUpgradeButtonSize);
    upgradeButton = std::make_shared<CButton>(ButtonZOrder, rect.center(),
                  rect.size(),
                  &game->r->buttonUpgrade, &game->r->buttonUpgrade, &game->r->buttonUpgrade,
                  game, eBTcannonUpgrade);
    connect(upgradeButton.get(), SIGNAL(pressed(eButtonType)),
            this, SLOT(onButtonPressed(eButtonType)));
    
    
    rect = QRectF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  CannonUpgradeButtonSize,
                  CannonUpgradeButtonSize);


    sellButton = std::make_shared<CButton>(ButtonZOrder, rect.center(),
                    rect.size(),
                    &game->r->buttonSell, &game->r->buttonSell, &game->r->buttonSell,
                    game, eBTcannonSell);

    connect(sellButton.get(), SIGNAL(pressed(eButtonType)),
            this, SLOT(onButtonPressed(eButtonType)));
}

void CCannonUpgrade::updateButtonsPositions()
{
    if (CloseButtonInInfoBlocksEnabled)
    {
        closeButton->setLeftTop(QPointF(center.x() - CannonUpgradeButtonSize/2,
                                      center.y() + CannonUpgradeRadius - CannonUpgradeButtonSize/2));
        closeButton->draw();
    }

    upgradeButton->setLeftTop(QPointF(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                     center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    upgradeButton->draw();

    sellButton->setLeftTop(QPointF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    sellButton->draw();
}

void CCannonUpgrade::show()
{
    CSceneObject::show();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton->show();

    upgradeButton->show();
    sellButton->show();
}

void CCannonUpgrade::hide()
{
    CSceneObject::hide();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton->hide();

    upgradeButton->hide();
    sellButton->hide();
}

void CCannonUpgrade::draw()
{
    CSceneObject::draw();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton->draw();

    upgradeButton->draw();
    sellButton->draw();
}

void CCannonUpgrade::onButtonPressed(eButtonType Type)
{
    switch (Type){
    case eBTCloseButton:
        break;
    case eBTcannonUpgrade:
        game->cannons[game->selectedCell.x()][game->selectedCell.y()]->upgrade();
        break;
    case eBTcannonSell:
        game->sellCannon(game->selectedCell);
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << Type;
    }
    game->deselectCell();
}
