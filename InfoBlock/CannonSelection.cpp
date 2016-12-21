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
        //cannonButton[i].init();
    }
}

void CCannonSelection::updateButtonsPositions()
{
    closeButton.setLeftTop(QPointF(center.x() - CannonSelectionButtonSize/2,
                                  center.y() + CannonSelectionRadius - CannonSelectionButtonSize/2));
    closeButton.draw();
}

void CCannonSelection::show()
{
    CGameObject::show();
    closeButton.show();
}

void CCannonSelection::hide()
{
    CGameObject::hide();
    closeButton.hide();
}

void CCannonSelection::onCloseButtonPressed()
{
    game->deselectCell();
}
