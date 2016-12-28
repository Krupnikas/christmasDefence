#include <SceneObject/SceneBackground.h>
#include <Game/Game.h>

CSceneBackground::CSceneBackground(CGame *game, QPixmap *pixmap)
{
    this->zOrder = BackgroundZOrder;
    this->game = game;
    this->pixmap = pixmap;
    this->position = game->scene->addBackgroundPixmap(pixmap);
}

void CSceneBackground::draw(){}
