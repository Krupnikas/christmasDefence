#pragma once

#include <Window.h>
#include <SceneObject/SceneBackground.h>

class CGame;
class CScene;

class CGameMenu: public IWindow
{
public:
    CGameMenu(CGame *game);

    //IWindow methods
    virtual void create() override;
    virtual void show() override;
    virtual void hide() override;
    virtual void resize() override;
    virtual void close() override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    CGame *game;

    std::shared_ptr<CSceneBackground> background;
};
