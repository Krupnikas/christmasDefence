#pragma once

#include <InfoBlock/IInfoBlock.h>

class CCannonSelection : public IInfoBlock
{
    Q_OBJECT
    
public:

    CCannonSelection(CGame *game, QPoint selectedCell);
    ~CCannonSelection();
    
    void updatePosition(QPoint selectedCell);
    
};
