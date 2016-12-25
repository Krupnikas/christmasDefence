#pragma once

#include <Game/Game.h>

class GameMenu
{
public:
    GameMenu(CGame *game);

    void open();
    void close();

    void onPlay();
    void onClose();

private:
    CScene *scene;
    CGame *game;
};
