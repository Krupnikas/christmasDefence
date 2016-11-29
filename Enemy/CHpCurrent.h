#pragma once

#include <Game/IGameObject.h>

class IEnemy;

class CHpCurrent : public IGameObject
{
    Q_OBJECT

public:
    CHpCurrent(IEnemy *enemy);
};
