#pragma once

#include <SceneObject/SceneObject.h>

class ICannon;

class CCannonRadius : public CSceneObject
{
    Q_OBJECT
    
public:
    CCannonRadius(ICannon *cannon);
    void upgrade(ICannon *cannon);
};

