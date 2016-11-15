#ifndef FASTCANNON_H
#define FASTCANNON_H

#include <Cannon/ICannon.h>

class FastCannon : public ICannon
{
    
public:
    
    FastCannon(Game *game, int cellX, int cellY, double hp, double angle, double globalRadius);
    ~FastCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
    
    
public slots:
    virtual void rotate();
    
};

#endif // FASTCANNON_H
