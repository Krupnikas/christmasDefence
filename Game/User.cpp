#include <Game/User.h>

CUser::CUser():
    cash(UserCash),
    hp(UserHp)
{
}

int CUser::getCash() const
{
    return cash;
}

void CUser::increaseCash(int value)
{
    cash += value;
}

void CUser::decreaseCash(int value)
{
    cashMutex.lock();
    if (cash >= value)
        cash -= value;
    cashMutex.unlock();
}

int CUser::getHp() const
{
    return hp;
}

void CUser::increaseHp(int value)
{
    hp += value;
}

void CUser::decreaseHp(int value)
{
    hpMutex.lock();    
    hp -= value;
    if (hp < 0)
        hp = 0;
    hpMutex.unlock();
}
