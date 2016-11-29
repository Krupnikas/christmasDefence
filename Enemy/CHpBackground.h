#pragma once

#include <Game/IGameObject.h>

class IEnemy;

class CHpBackground : public IGameObject
{
    Q_OBJECT

public:
    CHpBackground(IEnemy *enemy);
};
