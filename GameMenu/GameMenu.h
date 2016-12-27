#pragma once

#include <Window.h>
class CGame;
class CScene;

class GameMenu: public IWindow
{
public:
    GameMenu(CGame *game);

    //IWindow methods
    virtual void create() override;
    virtual void show() override;
    virtual void hide() override;
    virtual void resize() override;
    virtual void close() override;

private:
    CScene *scene;
    CGame *game;
};
