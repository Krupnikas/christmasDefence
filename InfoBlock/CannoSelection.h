#pragma once

#include <InfoBlock/IInfoBlock.h>

class CCannoSelection : public IInfoBlock
{
public:
    CCannoSelection(CGame *game, QPoint selectedCell);
    ~CCannoSelection();
};
