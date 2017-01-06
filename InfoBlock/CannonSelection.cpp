#include "CannonSelection.h"

CCannonSelection::CCannonSelection(CGame *game, QPoint SelectedCell)
{
    //IGameObject fields
    this->label = "Cannon Selection Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = 5;
    
    backgroundImageSize = CannonSelectionRadius * 8.0 / 3;
    this->textureSize = QSize(backgroundImageSize,
                              backgroundImageSize);
    this->pixmap = &game->r->cannonSelectionBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = game->cellCenter(SelectedCell);

    this->selectedCell = SelectedCell;

    initButtons();
    updatePosition(SelectedCell);

    connect(&game->user,
            SIGNAL(cashChanged(int)),
            this,
            SLOT(onCashChanged(int)));
}

CCannonSelection::~CCannonSelection()
{
}

void CCannonSelection::updatePosition(QPoint SelectedCell)
{
    center = game->cellCenter(SelectedCell);
    setLeftTop(center - QPointF(backgroundImageSize/2,
                                backgroundImageSize/2));
    selectedCell = SelectedCell;
    updateButtonsPositions();
}

void CCannonSelection::initButtons()
{
    if (CloseButtonInInfoBlocksEnabled)
    {
        QRectF closeRect(center.x() - CannonSelectionButtonSize/2,
                         center.y() + CannonSelectionRadius - CannonSelectionButtonSize/2,
                         CannonSelectionButtonSize,
                         CannonSelectionButtonSize);
        closeButton = std::make_shared<CButton>(
                    ButtonZOrder + 0.1, closeRect.center(),
                    closeRect.size(),
                    game, eBTCloseButton,
                    &game->r->buttonClose
                    );

        connect(closeButton.get(), SIGNAL(pressed(eButtonType)),
                this, SLOT(onButtonPressed(eButtonType)));
    }
    cannonButton.resize(TypesOfCannon);    
    for (int i = 0; i < TypesOfCannon; i++)
    {
        QRectF buttonRect(calculateTopLeftForButton(i),
                          QSize(CannonSelectionButtonSize,
                                CannonSelectionButtonSize));
        
        cannonButton[i] = std::make_shared<CButton>(
                    ButtonZOrder, buttonRect.center(),
                    buttonRect.size(),
                    game, static_cast<eButtonType>(eBTCloseButton + i + 1),
                    &game->r->cannonTypePreview[i]
                    );
        
        connect(cannonButton[i].get(), SIGNAL(pressed(eButtonType)),
                this, SLOT(onButtonPressed(eButtonType)));
    }
}

void CCannonSelection::updateButtonsPositions()
{
    QPoint topLeft;
    if (CloseButtonInInfoBlocksEnabled)
    {
        if (selectedCell.y() == 0)
        {
            topLeft.setX(center.x()
                         + CannonSelectionRadius
                         - CannonSelectionButtonSize / 2);

            topLeft.setY(center.y()
                         - CannonSelectionButtonSize / 2);

        } else if (selectedCell.y() == CellNumY - 1) {

            topLeft.setX(center.x()
                         + CannonSelectionRadius
                         - CannonSelectionButtonSize / 2);

            topLeft.setY(center.y()
                         - CannonSelectionButtonSize / 2);

        } else {
            topLeft = QPoint(center.x() - CannonSelectionButtonSize/2,
                                          center.y() + CannonSelectionRadius - CannonSelectionButtonSize/2);
        }
        closeButton->setLeftTop(topLeft);
        closeButton->draw();
    }

    for (int i = 0; i < TypesOfCannon; i++)
    {
       cannonButton[i]->setLeftTop(calculateTopLeftForButton(i));
       cannonButton[i]->draw();
    }
}

QPoint CCannonSelection::calculateTopLeftForButton(int i)
{

    QPoint topLeft;
    int c = (CloseButtonInInfoBlocksEnabled ? 1 : 0);

    if (selectedCell.y() == 0)
    {
        topLeft.setX(center.x()
                     - CannonSelectionRadius
                        * sin(-(i * 3.14 /(TypesOfCannon - 1 + c) - 1.57))
                     - CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + CannonSelectionRadius
                        * cos(-(i * 3.14 /(TypesOfCannon - 1 + c) - 1.57))
                     - CannonSelectionButtonSize / 2);

    } else if (selectedCell.y() == CellNumY - 1) {

        topLeft.setX(center.x()
                     - CannonSelectionRadius * sin((i + 2 * c) * 3.14 /(TypesOfCannon - 1 + c) + 1.57 * (1 - c))
                     - CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + CannonSelectionRadius * cos((i + 2 * c) * 3.14 /(TypesOfCannon - 1 + c) + 1.57 * (1 - c))
                     - CannonSelectionButtonSize / 2);

    } else {
        topLeft.setX(center.x()
                     - CannonSelectionRadius * sin((i + c) * 6.28 /(TypesOfCannon + c) + 0.785 * (1 - c))
                     - CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + CannonSelectionRadius * cos((i + c) * 6.28 /(TypesOfCannon + c) + 0.785 * (1 - c))
                     - CannonSelectionButtonSize / 2);
    }
    return topLeft;
}

int CCannonSelection::getCannonPrice(int i)
{
    switch (i){
    case 0:
        return FastCannonSmCost;
    case 1:
        return MonsterCannonSmCost;
    case 2:
        return SlowCannonSmCost;
    case 3:
        return BurnCannonSmCost;
    default:
        return 0;
    }
}

void CCannonSelection::show()
{
    CSceneObject::show();

    if (CloseButtonInInfoBlocksEnabled)
        closeButton->show();

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i]->show();
    }
}

void CCannonSelection::hide()
{
    CSceneObject::hide();
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->hide();

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i]->hide();
    }
}

void CCannonSelection::draw()
{
    CSceneObject::draw();
    if (CloseButtonInInfoBlocksEnabled)
        closeButton->draw();

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i]->draw();
    }
}

void CCannonSelection::onButtonPressed(eButtonType Type)
{
    switch (Type){
    case eBTCloseButton:
        break;
    case eBTChooseFast:
        game->buyCannon(std::make_shared<CFastCannon>(game, game->selectedCell, 0));
        break;
    case eBTChooseMonster:
        game->buyCannon(std::make_shared<CMonsterCannon>(game, game->selectedCell, 0));
        break;
    case eBTChooseSlow:
        game->buyCannon(std::make_shared<CSlowCannon>(game, game->selectedCell, 0));
        break;
    case eBTChooseBurn:
        game->buyCannon(std::make_shared<CBurnCannon>(game, game->selectedCell, 0));
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << Type;
    }
    game->deselectCell();
}

void CCannonSelection::onCashChanged(int newCash)
{/*
    for (int i = 0; i < TypesOfCannon; i++)
    {
        if (newCash < getCannonPrice(i))
        {
            //qDebug() << newCash << " trying to change pixmap to unable " << game->r->cannonUnableTypePreview[i];
            cannonButton[i]->setPixmap(&game->r->cannonUnableTypePreview[i]);
        } else {
            cannonButton[i]->setPixmap(&game->r->cannonTypePreview[i]);
        }
        cannonButton[i]->draw();
    }*/
}
