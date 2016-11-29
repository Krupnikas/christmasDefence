#pragma once

#include <Game/GameObject.h>
#include <Game/Game.h>


class CButton : public CGameObject
{
    Q_OBJECT

public:
    CButton();
    CButton(QRect ButtonRect, QPixmap *Pixmap,
            CGame *Game,
            qreal ZOrder = 10, qreal Angle = 0);
    ~CButton();

    QRect buttonRect;

    void init(QRect ButtonRect, QPixmap *Pixmap,
              CGame *Game,
              qreal ZOrder = 10, qreal Angle = 0);

public slots:
    void onMousePressed(QMouseEvent *event);

signals:
    void pressed();

};
