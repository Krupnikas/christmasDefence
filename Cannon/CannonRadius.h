#pragma once

#include <Game/GameObject.h>

class ICannon;

class CCannonRadius : public CGameObject
{
    Q_OBJECT
    
public:
    CCannonRadius(ICannon *cannon);
    void upgrade(ICannon *cannon);
};

