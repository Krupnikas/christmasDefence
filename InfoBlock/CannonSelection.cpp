#include "CannonSelection.h"

CCannonSelection::CCannonSelection(CGame *game, QPoint selectedCell)
{
    //IGameObject fields
    this->angle = 0;
    this->game = game;
    this->zOrder = 5;
    
    this->size = QSize(LocalWidth / 2 - OffsetX - 2 * CannonSelectionOffsetX,
                       LocalHeight - 2 * OffsetY - 2 *CannonSelectionOffsetY);    
    this->pixmap = &game->r->cannonSelectionBackground;
    this->position = game->scene->addPixmap(size, pixmap);
    
    if (selectedCell.x() > CellNumX / 2.0)
        this->leftTop = QPointF(OffsetX + CannonSelectionOffsetX,
                                OffsetY + CannonSelectionOffsetY);
    else
        this->leftTop = QPointF(CannonSelectionOffsetX + LocalWidth / 2,
                                OffsetY + CannonSelectionOffsetY);
    this->center = QPointF(leftTop.x() + size.width() / 2, leftTop.y() + size.height() + 2);
    
}

CCannonSelection::~CCannonSelection()
{
}

CCannonSelection::updatePosition(QPoint selectedCell)
{
    if (selectedCell.x() > CellNumX / 2.0)
    {
        this->leftTop = QPointF(OffsetX + CannonSelectionOffsetX,
                                OffsetY + CannonSelectionOffsetY);
    }
    else
    {
        this->leftTop = QPointF(CannonSelectionOffsetX + LocalWidth / 2,
                                OffsetY + CannonSelectionOffsetY);
    }
    draw();
}
