#include "CannonUpgrade.h"

CCannonUpgrade::CCannonUpgrade(CGame *game, QPoint SelectedCell)
{
    //IGameObject fields
    this->label = "Cannon Upgrade Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = 5;

    backgroundImageSize = CannonUpgradeRadius * 8.0 / 3;

    this->textureSize = QSize(backgroundImageSize,
                              backgroundImageSize);
    this->pixmap = game->r->cannonUpgradeBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->center = game->cellCenter(SelectedCell);

    this->selectedCell = SelectedCell;

    initButtons();
    updatePosition(SelectedCell);
}

void CCannonUpgrade::updatePosition(QPoint SelectedCell)
{
    center = game->cellCenter(SelectedCell);
    setLeftTop(center - QPointF(backgroundImageSize/2,
                                backgroundImageSize/2));
    selectedCell = SelectedCell;
    updateButtonsPositions();
    draw();
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
                    game, static_cast<int>(EButtonType::eBTCloseButton),
                    game->r->buttonClose
                    );

        connect(closeButton.get(), SIGNAL(pressed(int)),
                this, SLOT(onButtonPressed(int)));
    }

    QRectF rect(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                CannonUpgradeButtonSize,
                CannonUpgradeButtonSize);
    upgradeButton = std::make_shared<CButton>(ButtonZOrder, rect.center(),
                  rect.size(),
                  game, static_cast<int>(EButtonType::eBTcannonUpgrade),
                  game->r->buttonUpgrade);
    connect(upgradeButton.get(), SIGNAL(pressed(int)),
            this, SLOT(onButtonPressed(int)));
    
    
    rect = QRectF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  CannonUpgradeButtonSize,
                  CannonUpgradeButtonSize);


    sellButton = std::make_shared<CButton>(ButtonZOrder, rect.center(),
                    rect.size(),
                    game, static_cast<int>(EButtonType::eBTcannonSell),
                    game->r->buttonSell
                    );

    connect(sellButton.get(), SIGNAL(pressed(int)),
            this, SLOT(onButtonPressed(int)));
}

void CCannonUpgrade::updateButtonsPositions()
{
    if (CloseButtonInInfoBlocksEnabled)
    {
        closeButton->setLeftTop(QPointF(center.x() - CannonUpgradeButtonSize/2,
                                      center.y() + CannonUpgradeRadius - CannonUpgradeButtonSize/2));
        closeButton->draw();
    }

    if (selectedCell.y() == 0) {
        upgradeButton->setLeftTop(QPointF(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                         center.y() + sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));

        sellButton->setLeftTop(QPointF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                      center.y() + sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    } else {
    upgradeButton->setLeftTop(QPointF(center.x() - cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                     center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));

    sellButton->setLeftTop(QPointF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2));
    }

    upgradeButton->draw();
    sellButton->draw();
}

void CCannonUpgrade::scale()
{
    CSceneObject::scale();
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->scale();

    upgradeButton->scale();
    sellButton->scale();
}

void CCannonUpgrade::scaleWithLoss(QSizeF newSize)
{
    CSceneObject::scaleWithLoss(newSize);
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->scaleWithLoss(newSize);

    upgradeButton->scaleWithLoss(newSize);
    sellButton->scaleWithLoss(newSize);
}

void CCannonUpgrade::remove()
{
    CSceneObject::remove();
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->remove();

    upgradeButton->remove();
    sellButton->remove();
}

void CCannonUpgrade::draw()
{
    CSceneObject::draw();
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->draw();

    upgradeButton->draw();
    sellButton->draw();
}

void CCannonUpgrade::hide()
{
    CSceneObject::hide();

    int posX = selectedCell.x();
    int posY = selectedCell.y();
    if (!game->cannons[posX][posY])
        qDebug() << "CCannonUpgrade: hide: no cannon at selectedCell";
    else
        game->cannons[posX][posY]->hideRadius();
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->hide();

    upgradeButton->hide();
    sellButton->hide();
    
    game->selectionStatus = ESelectionStatus::eNone;
}

void CCannonUpgrade::show()
{
    CSceneObject::show();
    
    int posX = selectedCell.x();
    int posY = selectedCell.y();
    if (!game->cannons[posX][posY])
        qDebug() << "CCannonUpgrade: show: no cannon at selectedCell";
    else
        game->cannons[posX][posY]->showRadius();
    
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->show();

    upgradeButton->show();
    sellButton->show();
    
    game->selectionStatus = ESelectionStatus::eCannonUpgrade;
}

void CCannonUpgrade::onButtonPressed(int type)
{
    EButtonType eType = static_cast<EButtonType>(type);
    
    switch (eType){
    case EButtonType::eBTCloseButton:
        break;
    case EButtonType::eBTcannonUpgrade:
        game->cannons[selectedCell.x()][selectedCell.y()]->upgrade();
        break;
    case EButtonType::eBTcannonSell:
        game->sellCannon(selectedCell);
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << type;
    }
    game->deselectCell();
}
