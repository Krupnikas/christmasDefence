#include "CannoSelection.h"

CCannoSelection::CCannoSelection(CGame *game, QPoint selectedCell)
{
    this->game = game;
    if (selectedCell.x() > CellNumX / 2.0)
    {
     //block must be at the left side
    }
    else
    {
     //block must be at the right side
    }
}

CCannoSelection::~CCannoSelection(){}
