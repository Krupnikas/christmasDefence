#include <Game/User.h>

CUser::CUser(R *r):
    r(r),
    cash(UserCash),
    hp(UserHp)
{
    cashSound.setSource(r->url_cash);
    cashSound.setVolume(SoundLevel);
}

int CUser::getCash() const
{
    return cash;
}

void CUser::setCash(int value)
{
    cash = value;
    emit cashChanged(cash);
}

void CUser::increaseCash(int value)
{
    cash += value;
    cashSound.play();
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

void CUser::setHp(int value)
{
    hp = value;
    emit hpChanged(hp);
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
