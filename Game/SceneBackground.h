#pragma once

#include <Game/GameObject.h>

class SceneBackground: public CGameObject
{
public:
    SceneBackground(CGame *game, QPixmap *pixmap);

    virtual void draw() override;
};
