#pragma once

#include <SceneObject/SceneBackground.h>

class CGameBackground: public CSceneBackground
{
public:
    CGameBackground(CGame *game);

    virtual void scale() override;
    virtual void scaleWithLoss(QSizeF newSize) override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

private:
    std::shared_ptr<CSceneObject> fieldBackground;
    std::vector<std::vector<std::shared_ptr<CSceneObject>>> cells;
};
