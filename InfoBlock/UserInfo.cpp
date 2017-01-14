#include "UserInfo.h"

CUserInfo::CUserInfo(CGame *game)
{
    //IGameObject fields
    this->label = "User Information Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = m::UserInfoOnSides;

    this->textureSize = QSize(m::OffsetX,
                              m::OffsetY + m::CellSize * (m::CellNumY / 2 - 1));
    this->pixmap = game->r->userInfoBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->leftTop = QPointF(0, 0);

    hp = std::make_shared<CImageAndNumber>(game,
                                           game->r->hp_icon,
                                           QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                                  INTERNAL_OFFSET_Y),
                                                 QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                                       (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
    coins = std::make_shared<CImageAndNumber>(game,
                                           game->r->coins_icon,
                                           QRect(leftTop.toPoint() + QPoint(INTERNAL_OFFSET_X,
                                                                  INTERNAL_OFFSET_Y * 2 + (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2),
                                                 QSize(textureSize.width() - 2 * INTERNAL_OFFSET_X,
                                                       (textureSize.height() - 3 * INTERNAL_OFFSET_Y)/2)));
    connect(&game->userManager,
            SIGNAL(hpChanged(int)),
            this,
            SLOT(onHpChanged(int)));

    connect(&game->userManager,
            SIGNAL(cashChanged(int)),
            this,
            SLOT(onCashChanged(int)));
    hp->changeText(QString::number(game->userManager.getHp()));
    coins->changeText(QString::number(game->userManager.getCash()));
}

void CUserInfo::draw()
{
    CSceneObject::draw();
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

void CUserInfo::hide()
{
    CSceneObject::hide();
    hp->hide();
    coins->hide();
}

void CUserInfo::show()
{
    CSceneObject::show();
    hp->show();
    coins->show();
}

void CUserInfo::scale()
{
    CSceneObject::scale();
    hp->scale();
    coins->scale();
}

void CUserInfo::remove()
{
    hp->remove();
    coins->remove();
    CSceneObject::remove();
}

void CUserInfo::onHpChanged(int newHp)
{
    this->hp->changeText(QString::number(newHp));
    hp->draw();
    hp->show();
}

void CUserInfo::onCashChanged(int newCash)
{
    this->coins->changeText(QString::number(newCash));
    coins->draw();
    coins->show();
}
