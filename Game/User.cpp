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
    emit cashChanged(cash);
}

void CUser::decreaseCash(int value)
{
    cashMutex.lock();
    if (cash >= value)
        cash -= value;
    cashMutex.unlock();
    emit cashChanged(cash);
}

int CUser::getHp() const
{
    return hp;
}

void CUser::increaseHp(int value)
{
    hp += value;
    emit hpChanged(hp);
}

void CUser::decreaseHp(int value)
{
    hpMutex.lock();    
    hp -= value;
    if (hp < 0)
        hp = 0;
    hpMutex.unlock();
    emit hpChanged(hp);
}
