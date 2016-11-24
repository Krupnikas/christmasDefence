#pragma once

#include <Enemy/IEnemy.h>

class CGame;

const qreal Delta = 10;

class CFastEnemy : public IEnemy
{
    Q_OBJECT
    
public:
    
    CFastEnemy(CGame *game);
    
    virtual bool move();    
};
