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
    this->pixmap = &game->r->cannonUpgradeBackground;
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
                    game, static_cast<int>(eButtonType::eBTCloseButton),
                    &game->r->buttonClose
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
                  game, static_cast<int>(eButtonType::eBTcannonUpgrade),
                  &game->r->buttonUpgrade);
    connect(upgradeButton.get(), SIGNAL(pressed(int)),
            this, SLOT(onButtonPressed(int)));
    
    
    rect = QRectF(center.x() + cos(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  center.y() - sin(1) * CannonUpgradeRadius - CannonUpgradeButtonSize/2,
                  CannonUpgradeButtonSize,
                  CannonUpgradeButtonSize);


    sellButton = std::make_shared<CButton>(ButtonZOrder, rect.center(),
                    rect.size(),
                    game, static_cast<int>(eButtonType::eBTcannonSell),
                    &game->r->buttonSell
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

void CCannonUpgrade::onButtonPressed(int type)
{
    eButtonType eType = static_cast<eButtonType>(type);
    
    switch (eType){
    case eButtonType::eBTCloseButton:
        break;
    case eButtonType::eBTcannonUpgrade:
        game->cannons[game->selectedCell.x()][game->selectedCell.y()]->upgrade();
        break;
    case eButtonType::eBTcannonSell:
        game->sellCannon(game->selectedCell);
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << type;
    }
    game->deselectCell();
}
