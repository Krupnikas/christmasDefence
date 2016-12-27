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

    hp = std::make_shared<CImageAndNumber>(game,
                                           &game->r->hpIcon,
                                           QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                                  INTERNAL_OFFSET_Y),
                                                 QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                                       (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
    coins = std::make_shared<CImageAndNumber>(game,
                                           &game->r->coinsIcon,
                                           QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                                  INTERNAL_OFFSET_Y * 2 + (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2),
                                                 QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                                       (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
}

void CUserInfo::draw()
{
    CGameObject::draw();
    hp->updatePosition(QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                        INTERNAL_OFFSET_Y),
                                       QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                             (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
    hp->draw();
    coins->updatePosition(QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                           INTERNAL_OFFSET_Y * 2 + (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2),
                                          QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                                (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
    coins->draw();
}

void CUserInfo::show()
{
    CGameObject::show();
    hp->show();
    coins->show();
}

void CUserInfo::scaleItem()
{
    CGameObject::scaleItem();
    hp->scaleItem();
    coins->scaleItem();
}
