#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <Game/Button.h>
#include <Cannon/ICannon.h>

class CCannonUpgrade : public IInfoBlock
{
      Q_OBJECT
public:
    CCannonUpgrade(CGame *game, QPoint selectedCell);
};

