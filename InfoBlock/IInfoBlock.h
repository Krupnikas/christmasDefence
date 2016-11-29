#pragma once

#include <Game/GameObject.h>
#include <Game/Game.h>
#include <Game/Button.h>

class CGame;

class IInfoBlock : public CGameObject
{     
    Q_OBJECT
    
public:

    IInfoBlock();
    virtual ~IInfoBlock();

public slots:
    virtual void onTimer();
};
