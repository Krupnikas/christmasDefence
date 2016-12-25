#include "UserInfo.h"

CUserInfo::CUserInfo(CGame *game)
{
    //IGameObject fields
    this->label = "User Information Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = UserInfoOnSides;

    this->textureSize = QSize(OffsetX,
                              OffsetY + CellSize * (CellNumY / 2));
    this->pixmap = &game->r->userInfoBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->leftTop = QPointF(0, 0);
}
