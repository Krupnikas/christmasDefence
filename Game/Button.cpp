#include "Button.h"

CButton::CButton(){}

CButton::CButton(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    init(ButtonRect, Pixmap, Game, ZOrder, Angle);
}

CButton::~CButton(){}

void CButton::init(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    this->buttonRect = ButtonRect;
    this->textureSize = QSizeF(buttonRect.width(),
                         buttonRect.height());
    this->game = Game;
    this->zOrder =ZOrder;
    this->angle = Angle;
    this->pixmap = Pixmap;

    position = game->scene->addPixmap(textureSize, pixmap);

    this->center = buttonRect.center();
    this->leftTop = buttonRect.topLeft();

    connect(game, SIGNAL(mousePressed(QMouseEvent*)),
            this, SLOT(onMousePressed(QMouseEvent*)));
}

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
