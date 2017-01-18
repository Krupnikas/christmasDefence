#pragma once

#include <Bullet/IBullet.h>

class ICannon;

class CMonsterBullet : public IBullet
{
public:
    CMonsterBullet(CGame *game, std::shared_ptr<ICannon> cannon, double angle, ESizeType type);
};
