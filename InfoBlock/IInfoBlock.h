#pragma once

#include <SceneObject/SceneObject.h>
#include <Game/Game.h>
#include <SceneObject/Button.h>

class CGame;

class IInfoBlock : public CSceneObject
{     
    Q_OBJECT
    
public:

    IInfoBlock();
    virtual ~IInfoBlock();

public slots:
    virtual void onTimer();
};
