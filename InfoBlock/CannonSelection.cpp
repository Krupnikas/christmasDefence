#include "CannonSelection.h"

CCannoSelection::CCannoSelection(CGame *game, QPoint selectedCell)
{
    this->game = game;
    this->pixmap = &game->r->cannonSelectionBackground;
    this->size = QSize(LocalWidth / 2 - OffsetX - 2 * myOffsetX,
                       LocalHeight - 2 * OffsetY - 2 *myOffsetY);
    this->leftTop = QPointF(OffsetX + myOffsetX,
                            OffsetY + myOffsetY);

    if (selectedCell.x() > CellNumX / 2.0)
    {
        this->leftTop = QPointF(OffsetX + myOffsetX,
                                OffsetY + myOffsetY);
    }
    else
    {
        this->leftTop = QPointF(myOffsetX + LocalWidth / 2,
                                OffsetY + myOffsetY);
    }
    position = game->scene->drawAndPosition(leftTop.x(), leftTop.y(),
                                            size.width(), size.height(),
                                            pixmap, 0, 5);
}

CCannoSelection::~CCannoSelection()
{
    game->scene->removeItem(position);
}
