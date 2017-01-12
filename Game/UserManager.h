#pragma once

#include <Resource.h>

class CGame;

class CUserManager : public QObject
{
    Q_OBJECT
public:
    CUserManager(CGame *game);
        
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
    CGame *game;
    
    std::mutex cashMutex;
    int cash;
    
    std::mutex hpMutex;
    int hp;
    
    QSoundEffect cashSound;
};
