#pragma once

#include <Bullet/IBullet.h>

class ICannon;

class CFastBullet : public IBullet
{
public:
    CFastBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type);
    
};
