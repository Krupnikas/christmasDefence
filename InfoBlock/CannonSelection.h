#pragma once

#include <InfoBlock/IInfoBlock.h>

class CCannoSelection : public IInfoBlock
{
    Q_OBJECT
    
public:

    
    CCannoSelection(CGame *game, QPoint selectedCell);
    ~CCannoSelection();
    
    updatePosition(QPoint selectedCell);
    
};
