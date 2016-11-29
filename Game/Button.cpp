#include "Button.h"

CButton::CButton(){}

CButton::CButton(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    buttonRect = ButtonRect;
    center = buttonRect.center();
    leftTop = buttonRect.topLeft();
    textureSize = QSizeF(buttonRect.width(),
                         buttonRect.height());
    game = Game;
    zOrder =ZOrder;
    angle = Angle;
    pixmap = Pixmap;
    position = game->scene->addPixmap(textureSize, pixmap);

    connect(game, SIGNAL(mousePressed(QMouseEvent*)),
            this, SLOT(onMousePressed(QMouseEvent*)));
}

CButton::~CButton(){}

void CButton::onMousePressed(QMouseEvent *event)
{
    if (buttonRect.contains(QPoint(event->localPos().x(),
                                   event->localPos().y()))
                            && position->isVisible())
    {
        event->accept();
        emit pressed();
    }
}
