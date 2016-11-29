#pragma once

#include <Game/IGameObject.h>
#include <Game/Game.h>
#include <Game/Button.h>

class CGame;

class IInfoBlock : public IGameObject
{     
    Q_OBJECT
    
public:

    IInfoBlock();
    virtual ~IInfoBlock();

public slots:
    virtual void onTimer();
};
