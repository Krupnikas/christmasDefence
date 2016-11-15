#ifndef FASTBULLET_H
#define FASTBULLET_H

#include <Bullet/IBullet.h>

class FastBullet : public IBullet
{
public:
    
    FastBullet(Game *game, int centerX, int centerY, double angle);
    
    virtual void draw();
    virtual void move();
};

#endif // FASTBULLET_H
