#pragma once

#include <SceneObject/SceneBackground.h>

class CGameBackground: CSceneBackground
{
public:
    CGameBackground();

    virtual void scale() override;
    virtual void scaleWithLoss(QSizeF newSize) override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

private:
    std::shared_ptr<CSceneObject> fieldBackground;
};
