#pragma once

#include <Window.h>
#include <SceneObject/SceneBackground.h>
#include <SceneObject/Button.h>

class CGame;
class CScene;

class CGameMenu: public IWindow
{
    Q_OBJECT
    
public:
    CGameMenu(CGame *game);

    //IWindow methods
    virtual void create() override;
    virtual void show() override;
    virtual void hide() override;
    virtual void resize() override;
    virtual void close() override;
    
private slots:
    void onButtonPressed(int type);

private:
    CGame *game;

    std::shared_ptr<CSceneBackground> background;
    std::shared_ptr<CSceneObject> caption;
    
    std::vector<std::shared_ptr<CButton>> buttons;
};
