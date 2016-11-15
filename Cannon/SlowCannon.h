#ifndef SLOWCANNON_H
#define SLOWCANNON_H

#include <Cannon/ICannon.h>

class SlowCannon : public ICannon
{
private:
    
public:
    
    SlowCannon();
    ~SlowCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
    
public slots:
    virtual void rotate(){}
};

#endif // SLOWCANNON_H
