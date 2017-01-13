#include "CannonSelection.h"

CCannonSelection::CCannonSelection(CGame *game, QPoint selectedCell)
{
    //IGameObject fields
    this->label = "Cannon Selection Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = m::GameInfoblockZOrder;
    
    backgroundImageSize = m::CannonSelectionRadius * 8.0 / 3;
    this->textureSize = QSize(backgroundImageSize,
                              backgroundImageSize);
    this->pixmap = game->r->cannonSelectionBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);
    
    this->center = game->cellCenter(selectedCell);

    this->selectedCell = selectedCell;

    cellSelection = std::make_shared<CSceneObject>(
                0, m::GameBackgroundZOrder,
                QPointF(0, 0), QSizeF(m::CellSize, m::CellSize),
                game->r->cellSelected, game);
    
    initButtons();
    updatePosition(selectedCell);

    connect(&game->userManager,
            SIGNAL(cashChanged(int)),
            this,
            SLOT(onCashChanged(int)));
}

CCannonSelection::~CCannonSelection()
{
}

void CCannonSelection::updatePosition(QPoint selectedCell)
{
    this->selectedCell = selectedCell;
    
    center = game->cellCenter(selectedCell);
    leftTop = center - QPointF(backgroundImageSize/2,
                               backgroundImageSize/2);
    
    QSizeF cellSize = cellSelection->getSize();
    cellSelection->setLeftTop(center - QPointF(cellSize.width(), cellSize.height()));
    updateButtonsPositions();
    
    draw();
}


void CCannonSelection::updateButtonsPositions()
{
    QPoint topLeft;
    if (m::CloseButtonInInfoBlocksEnabled)
    {
        if (selectedCell.y() == 0)
        {
            topLeft.setX(center.x()
                         + m::CannonSelectionRadius
                         - m::CannonSelectionButtonSize / 2);

            topLeft.setY(center.y()
                         - m::CannonSelectionButtonSize / 2);

        } else if (selectedCell.y() == m::CellNumY - 1) {

            topLeft.setX(center.x()
                         + m::CannonSelectionRadius
                         - m::CannonSelectionButtonSize / 2);

            topLeft.setY(center.y()
                         - m::CannonSelectionButtonSize / 2);

        } else {
            topLeft = QPoint(center.x() - m::CannonSelectionButtonSize/2,
                                          center.y() + m::CannonSelectionRadius - m::CannonSelectionButtonSize/2);
        }
        closeButton->setLeftTop(topLeft);
    }

    for (int i = 0; i < m::TypesOfCannon; i++)
       cannonButton[i]->setLeftTop(calculateTopLeftForButton(i));
}

void CCannonSelection::initButtons()
{
    if (m::CloseButtonInInfoBlocksEnabled)
    {
        QRectF closeRect(center.x() - m::CannonSelectionButtonSize/2,
                         center.y() + m::CannonSelectionRadius - m::CannonSelectionButtonSize/2,
                         m::CannonSelectionButtonSize,
                         m::CannonSelectionButtonSize);
        closeButton = std::make_shared<CButton>(
                    m::ButtonZOrder + 0.1, closeRect.center(),
                    closeRect.size(),
                    game, static_cast<int>(EButtonType::eBTCloseButton),
                    game->r->buttonClose
                    );

        connect(closeButton.get(), SIGNAL(pressed(int)),
                this, SLOT(onButtonPressed(int)));
    }
    
    cannonButton.resize(m::TypesOfCannon);    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        QRectF buttonRect(calculateTopLeftForButton(i),
                          QSize(m::CannonSelectionButtonSize,
                                m::CannonSelectionButtonSize));
        
        cannonButton[i] = std::make_shared<CButton>(
                    m::ButtonZOrder, buttonRect.center(),
                    buttonRect.size(),
                    game, static_cast<int>(EButtonType::eBTCloseButton) + i + 1,
                    game->r->cannonTypePreview[i]
                    );
        
        connect(cannonButton[i].get(), SIGNAL(pressed(int)),
                this, SLOT(onButtonPressed(int)));
    }
}

QPoint CCannonSelection::calculateTopLeftForButton(int i)
{

    QPoint topLeft;
    int c = (m::CloseButtonInInfoBlocksEnabled ? 1 : 0);

    if (selectedCell.y() == 0)
    {
        topLeft.setX(center.x()
                     - m::CannonSelectionRadius
                        * sin(-(i * 3.14 /(m::TypesOfCannon - 1 + c) - 1.57))
                     - m::CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + m::CannonSelectionRadius
                        * cos(-(i * 3.14 /(m::TypesOfCannon - 1 + c) - 1.57))
                     - m::CannonSelectionButtonSize / 2);

    } else if (selectedCell.y() == m::CellNumY - 1) {

        topLeft.setX(center.x()
                     - m::CannonSelectionRadius * sin((i + 2 * c) * 3.14 /(m::TypesOfCannon - 1 + c) + 1.57 * (1 - c))
                     - m::CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + m::CannonSelectionRadius * cos((i + 2 * c) * 3.14 /(m::TypesOfCannon - 1 + c) + 1.57 * (1 - c))
                     - m::CannonSelectionButtonSize / 2);

    } else {
        topLeft.setX(center.x()
                     - m::CannonSelectionRadius * sin((i + c) * 6.28 /(m::TypesOfCannon + c) + 0.785 * (1 - c))
                     - m::CannonSelectionButtonSize / 2);

        topLeft.setY(center.y()
                     + m::CannonSelectionRadius * cos((i + c) * 6.28 /(m::TypesOfCannon + c) + 0.785 * (1 - c))
                     - m::CannonSelectionButtonSize / 2);
    }
    return topLeft;
}

int CCannonSelection::getCannonPrice(int i)
{
    switch (i){
    case 0:
        return m::FastCannonSmCost;
    case 1:
        return m::MonsterCannonSmCost;
    case 2:
        return m::SlowCannonSmCost;
    case 3:
        return m::BurnCannonSmCost;
    default:
        return 0;
    }
}

void CCannonSelection::scale()
{
    CSceneObject::scale();
    cellSelection->scale();
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->scale();
    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonButton[i]->scale();
    }    
}

void CCannonSelection::scaleWithLoss(QSizeF newSize)
{
    CSceneObject::scaleWithLoss(newSize);
    cellSelection->scaleWithLoss(newSize);
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->scaleWithLoss(newSize);
    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonButton[i]->scaleWithLoss(newSize);
    }
}

void CCannonSelection::remove()
{
    CSceneObject::remove();
    cellSelection->remove();
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->remove();
    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonButton[i]->remove();
    }   
}

void CCannonSelection::show()
{
    CSceneObject::show();
    cellSelection->show();
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->show();
    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonButton[i]->show();
    }
    game->selectionStatus = ESelectionStatus::eCannonSelection;
}

void CCannonSelection::hide()
{
    CSceneObject::hide();    
    cellSelection->hide();    
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->hide();

    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonButton[i]->hide();
    }
    
    game->selectionStatus = ESelectionStatus::eNone;
}

void CCannonSelection::draw()
{
    CSceneObject::draw();
    cellSelection->draw();
    
    if (m::CloseButtonInInfoBlocksEnabled)
        closeButton->draw();

    for (int i = 0; i < m::TypesOfCannon; i++)
        cannonButton[i]->draw();
}

void CCannonSelection::onButtonPressed(int type)
{
    EButtonType eType = static_cast<EButtonType>(type);
    
    switch (eType){
    case EButtonType::eBTCloseButton:
        break;
    case EButtonType::eBTChooseFast:
        game->buyCannon(std::make_shared<CFastCannon>(game, selectedCell, 0));
        break;
    case EButtonType::eBTChooseMonster:
        game->buyCannon(std::make_shared<CMonsterCannon>(game, selectedCell, 0));
        break;
    case EButtonType::eBTChooseSlow:
        game->buyCannon(std::make_shared<CSlowCannon>(game, selectedCell, 0));
        break;
    case EButtonType::eBTChooseBurn:
        game->buyCannon(std::make_shared<CBurnCannon>(game, selectedCell, 0));
        break;
    default:
        qDebug() << "Cannon Selection error! need type number " << type;
    }
    
    hide();
}

void CCannonSelection::onCashChanged(int)
{/*
    for (int i = 0; i < TypesOfCannon; i++)
    {
        if (newCash < getCannonPrice(i))
        {
            //qDebug() << newCash << " trying to change pixmap to unable " << game->r->cannonUnableTypePreview[i];
            cannonButton[i]->setPixmap(game->r->cannonUnableTypePreview[i]);
        } else {
            cannonButton[i]->setPixmap(game->r->cannonTypePreview[i]);
        }
        cannonButton[i]->draw();
    }*/
}
