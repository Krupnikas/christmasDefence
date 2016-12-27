#include <Game/SceneBackground.h>
#include <Game/Game.h>

SceneBackground::SceneBackground(CGame *game, QPixmap *pixmap)
{
    this->game = game;
    this->pixmap = pixmap;
    this->position = game->scene->addBackgroundPixmap(pixmap);
}

void SceneBackground::draw(){}
