#pragma once

#include <Game/Resource.h>

class CUser
{
public:
    CUser();
    
    
    
    int getCash() const;
    void increaseCash(int value);
    void decreaseCash(int value);
    
    int getHp() const;
    void increaseHp(int value);
    void decreaseHp(int value);
    
private:
    std::mutex cashMutex;
    int cash;
    
    std::mutex hpMutex;
    int hp;
};
