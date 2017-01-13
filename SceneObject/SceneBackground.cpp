#include <SceneObject/SceneBackground.h>
#include <Game/Game.h>

CSceneBackground::CSceneBackground(CGame *game, std::shared_ptr<QPixmap> pixmap)
{
    this->zOrder = m::BackgroundZOrder;
    this->game = game;
    this->pixmap = pixmap;
    this->position = game->scene->addBackgroundPixmap(pixmap);
}

void CSceneBackground::scale()
{
    if (position)
        game->scene->removeItem(position);
    position = game->scene->addBackgroundPixmap(pixmap);
}

void CSceneBackground::draw(){}
