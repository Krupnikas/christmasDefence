#pragma once

#include <Bullet/IBullet.h>

class ICannon;

class CBurnBullet : public IBullet
{
public:
    CBurnBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type);
};
