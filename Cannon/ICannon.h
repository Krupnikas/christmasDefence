#ifndef CANNON_H
#define CANNON_H

class ICannon
{     
    enum CannonType {
        SMALL, MEDIUM, BIG
    };

private:

    double hp;
    double angle;
    double globalRadius;    
    
public:

    ICannon();
    ~ICannon();

    virtual void draw();
    virtual void fire();

};

#endif // CANNON_H
