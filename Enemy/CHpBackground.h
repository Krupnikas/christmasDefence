#pragma once

#include <Game/GameObject.h>

class IEnemy;

class CHpBackground : public CGameObject
{
    Q_OBJECT

public:
    CHpBackground(IEnemy *enemy);
};
