#pragma once

#include <Bullet/IBullet.h>

class ICannon;

class CSlowBullet : public IBullet
{
public:
    CSlowBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type);
};
