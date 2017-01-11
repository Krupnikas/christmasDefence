#pragma once

#include <Enemy/IEnemy.h>

class CGame;

const qreal Delta = 10;

class CFastEnemy : public IEnemy
{
    Q_OBJECT
    
public:
    
    CFastEnemy(CGame *game, int enemyTexture, int enemyPower);
    
protected:
    virtual std::shared_ptr<QPixmap> getTexture(int enemyTexture);
};
