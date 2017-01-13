#include <Game/UserManager.h>
#include <Game/Game.h>
#include <InfoBlock/UserInfo.h>

CUserManager::CUserManager(CGame *game):
    game(game),
    cash(UserCash),
    hp(UserHp)
{
    cashSound.setSource(game->r->url_cash);
    cashSound.setVolume(m::SoundLevel);
}

int CUserManager::getCash() const
{
    return cash;
}

void CUserManager::setCash(int value)
{
    cash = value;
    emit cashChanged(cash);
}

void CUserManager::increaseCash(int value)
{
    cash += value;
    cashSound.play();
    emit cashChanged(cash);
}

void CUserManager::decreaseCash(int value)
{
    cashMutex.lock();
    if (cash >= value)
        cash -= value;
    cashMutex.unlock();
    emit cashChanged(cash);
}

int CUserManager::getHp() const
{
    return hp;
}

void CUserManager::setHp(int value)
{
    hp = value;
    emit hpChanged(hp);
}

void CUserManager::increaseHp(int value)
{
    hp += value;
    emit hpChanged(hp);
}

void CUserManager::decreaseHp(int value)
{
    hpMutex.lock();    
    hp -= value;
    if (hp < 0)
        hp = 0;
    hpMutex.unlock();
    emit hpChanged(hp);
}
