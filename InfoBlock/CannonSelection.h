#pragma once

#include <InfoBlock/IInfoBlock.h>

class CCannoSelection : public IInfoBlock
{
public:

    const int myOffsetX = 50;
    const int myOffsetY = 50;

    CCannoSelection(CGame *game, QPoint selectedCell);
    ~CCannoSelection();
};
