#pragma once

#include <Resource.h>

class CUser : public QObject
{
    Q_OBJECT
public:
    CUser(R *r);
        
    int getCash() const;
    void setCash(int value);
    void increaseCash(int value);
    void decreaseCash(int value);
    
    int getHp() const;
    void setHp(int value);
    void increaseHp(int value);
    void decreaseHp(int value);
    
signals:
    void hpChanged(int newHp);
    void cashChanged(int newCash);
    
private:
    R *r;
    
    std::mutex cashMutex;
    int cash;
    
    std::mutex hpMutex;
    int hp;
    
    QSoundEffect cashSound;
};
