#pragma once

#include <SceneObject/SceneObject.h>

class IEnemy;

class CHpCurrent : public CSceneObject
{
    Q_OBJECT

public:
    CHpCurrent(IEnemy *enemy);
};
