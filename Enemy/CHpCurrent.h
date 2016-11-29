#pragma once

#include <Game/GameObject.h>

class IEnemy;

class CHpCurrent : public CGameObject
{
    Q_OBJECT

public:
    CHpCurrent(IEnemy *enemy);
};
