#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Game/Button.h>

class CCannonSelection : public IInfoBlock
{
    Q_OBJECT
    
public:

    CCannonSelection(CGame *game, QPoint selectedCell);
    ~CCannonSelection();
    
    std::shared_ptr<CButton> closeButton;

    void updatePosition(QPoint selectedCell);
    
};
