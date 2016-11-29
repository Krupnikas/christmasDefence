#include "Button.h"

CButton::CButton(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    buttonRect = ButtonRect;
    center = buttonRect.center();
    leftTop = buttonRect.topLeft();
    textureSize = QSizeF(buttonRect.width(),
                         buttonRect.height());
    pixmap = Pixmap;
    game = Game;
    zOrder =ZOrder;
    angle = Angle;
}

void CButton::onMousePressed(QMouseEvent *event)
{
    if (buttonRect.contains(QPoint(event->localPos().x(),
                                   event->localPos().y())))
    {
        event->accept();
        emit pressed();
    }
}
