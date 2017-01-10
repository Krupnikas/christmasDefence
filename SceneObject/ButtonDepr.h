#pragma once

#include <SceneObject/SceneObject.h>
#include <Game/Game.h>


class CButtonDepr : public CSceneObject
{
    Q_OBJECT

public:
    CButtonDepr();
    CButtonDepr(EButtonType Type, QRect ButtonRect, QPixmap *Pixmap,
            CGame *Game,
            qreal ZOrder = 10, qreal Angle = 0);
    ~CButtonDepr();

    EButtonType type;

    QRect buttonRect;

    virtual void show() override;

    void init(EButtonType Type, QRect ButtonRect, QPixmap *Pixmap,
              CGame *Game,
              qreal ZOrder = 10, qreal Angle = 0);

public slots:
    void onMousePressed(QMouseEvent *event);

signals:
    void pressed(EButtonType Type);

};
