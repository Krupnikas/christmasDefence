#ifndef BURNCANNON_H
#define BURNCANNON_H

#include <Cannon/ICannon.h>

class BurnCannon : public ICannon
{
private:
    
public:
    
    BurnCannon();
    
    virtual ~BurnCannon();
    
    virtual void draw() override;
    virtual void fire(qreal angle) override;
    
public slots:
    virtual void rotate(){}
};

#endif // BURNCANNON_H
