#pragma once

#include <SceneObject/SceneObject.h>

class CSceneBackground: public CSceneObject
{
public:
    CSceneBackground(CGame *game, std::shared_ptr<QPixmap> pixmap);

    virtual void scale() override;
    virtual void draw() override;
};
