#include <Game/Button.h>
#include <Game/Game.h>

CButton::CButton(){}

CButton::CButton(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    qDebug() << "Button Created";
    init(ButtonRect, Pixmap, Game, ZOrder, Angle);
}

CButton::~CButton(){}

void CButton::draw()
{
    CGameObject::draw();
    buttonRect.moveLeft(leftTop.x());
    buttonRect.moveTop(leftTop.y());
}

void CButton::init(QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    label = "Button";
    buttonRect = ButtonRect;
    textureSize = QSizeF(buttonRect.width(),
                         buttonRect.height());
    game = Game;
    zOrder =ZOrder;
    angle = Angle;
    pixmap = Pixmap;

    position = game->scene->addPixmap(textureSize, pixmap);

    center = buttonRect.center();
    leftTop = buttonRect.topLeft();

    connect(game, SIGNAL(mousePressed(QMouseEvent*)),
            this, SLOT(onMousePressed(QMouseEvent*)));
}

void CButton::onMousePressed(QMouseEvent *event)
{
    qDebug() << event->localPos() << " is in " << buttonRect
             << buttonRect.contains(QPoint(event->localPos().x(),
                                                                event->localPos().y()));
    if (buttonRect.contains(QPoint(event->localPos().x(),
                                   event->localPos().y()))
                            && position->isVisible())
    {
        qDebug() << "One Of Buttons Pressed";
        event->accept();
        game->oneOfButtonPressed = true;
        emit pressed();
    }
}
