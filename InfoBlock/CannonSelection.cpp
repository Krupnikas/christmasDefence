#include "CannonSelection.h"

CCannonSelection::CCannonSelection(CGame *game, QPoint selectedCell)
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
    
    this->center = game->cellCenter(selectedCell);

    initButtons();
    updatePosition(selectedCell);

}

CCannonSelection::~CCannonSelection()
{
}

void CCannonSelection::updatePosition(QPoint selectedCell)
{
    center = game->cellCenter(selectedCell);
    setLeftTop(center - QPointF(backgroundImageSize/2,
                                backgroundImageSize/2));
    updateButtonsPositions();
}

void CCannonSelection::initButtons()
{
    closeButton.init(QRect(center.x() - CannonSelectionButtonSize/2,
                           center.y() + CannonSelectionRadius - CannonSelectionButtonSize/2,
                           CannonSelectionButtonSize,
                           CannonSelectionButtonSize),
                     &game->r->buttonClose,
                     game,
                     ButtonZOrder,
                     0);

    connect(&closeButton, SIGNAL(pressed()),
            this, SLOT(onCloseButtonPressed()));

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i].init(QRect(calculateTopLeftForButton(i),
                             QSize(CannonSelectionButtonSize,
                                   CannonSelectionButtonSize)),
                             &game->r->cannonTypePreview[i],
                             game,
                             ButtonZOrder,
                             0);
    }
}

void CCannonSelection::updateButtonsPositions()
{
    closeButton.setLeftTop(QPointF(center.x() - CannonSelectionButtonSize/2,
                                  center.y() + CannonSelectionRadius - CannonSelectionButtonSize/2));
    closeButton.draw();

    for (int i = 0; i < TypesOfCannon; i++)
    {
       cannonButton[i].setLeftTop(calculateTopLeftForButton(i));
       cannonButton[i].draw();
    }
}

QPoint CCannonSelection::calculateTopLeftForButton(int i)
{
    QPoint topLeft;

    topLeft.setX(center.x()
                 - CannonSelectionRadius * sin((i + 1) * 6.28 /(TypesOfCannon + 1))
                 - CannonSelectionButtonSize / 2);

    topLeft.setY(center.y()
                 + CannonSelectionRadius * cos((i + 1) * 6.28 /(TypesOfCannon + 1))
                 - CannonSelectionButtonSize / 2);

    return topLeft;
}

void CCannonSelection::show()
{
    CGameObject::show();
    closeButton.show();

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i].show();
    }
}

void CCannonSelection::hide()
{
    CGameObject::hide();
    closeButton.hide();

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonButton[i].hide();
    }
}

void CCannonSelection::onCloseButtonPressed()
{
    game->deselectCell();
}
