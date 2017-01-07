#pragma once

#include <Resource.h>

class CUser : public QObject
{
    Q_OBJECT
public:
    CUser();
        
    int getCash() const;
    void setCash(int value);
    void increaseCash(int value);
    void decreaseCash(int value);
    
    int getHp() const;
    void setHp(int value);
    void increaseHp(int value);
    void decreaseHp(int value);
    
private:
    std::mutex cashMutex;
    int cash;
    
    std::mutex hpMutex;
    int hp;

signals:
    void hpChanged(int newHp);
    void cashChanged(int newCash);
};
