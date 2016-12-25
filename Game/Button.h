#pragma once

#include <Game/GameObject.h>
#include <Game/Game.h>


class CButton : public CGameObject
{
    Q_OBJECT

public:
    CButton();
    CButton(eButtonTypes Type, QRect ButtonRect, QPixmap *Pixmap,
            CGame *Game,
            qreal ZOrder = 10, qreal Angle = 0);
    ~CButton();

    eButtonTypes type;

    QRect buttonRect;

    virtual void draw();
    virtual void show();
    virtual void scaleItem();

    void init(eButtonTypes Type, QRect ButtonRect, QPixmap *Pixmap,
              CGame *Game,
              qreal ZOrder = 10, qreal Angle = 0);

public slots:
    void onMousePressed(QMouseEvent *event);

signals:
    void pressed(eButtonTypes Type);

};
