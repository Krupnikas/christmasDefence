#pragma once

#include <SceneObject/SceneObject.h>
#include <Game/Game.h>


class CButton : public CSceneObject
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

    virtual void show() override;

    void init(eButtonTypes Type, QRect ButtonRect, QPixmap *Pixmap,
              CGame *Game,
              qreal ZOrder = 10, qreal Angle = 0);

public slots:
    void onMousePressed(QMouseEvent *event);

signals:
    void pressed(eButtonTypes Type);

};
