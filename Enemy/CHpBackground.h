#pragma once

#include <SceneObject/SceneObject.h>

class IEnemy;

class CHpBackground : public CSceneObject
{
    Q_OBJECT

public:
    CHpBackground(IEnemy *enemy);
};
