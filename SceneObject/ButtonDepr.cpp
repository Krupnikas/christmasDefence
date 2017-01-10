#include <SceneObject/ButtonDepr.h>
#include <Game/Game.h>

CButtonDepr::CButtonDepr(){}

CButtonDepr::CButtonDepr(EButtonType Type, QRect ButtonRect, QPixmap *Pixmap, CGame *Game,
                 qreal ZOrder, qreal Angle)
{
    qDebug() << "Button Created";
    init(Type, ButtonRect, Pixmap, Game, ZOrder, Angle);
}

CButtonDepr::~CButtonDepr(){}

void CButtonDepr::show()
{
    CSceneObject::show();
    buttonRect = QRect(0,
                       0,
                       game->scene->toLocalCX(position->boundingRect().width()),
                       game->scene->toLocalCX(position->boundingRect().height()));
    buttonRect.moveLeft(leftTop.x());
    buttonRect.moveTop(leftTop.y());
}

void CButtonDepr::init(EButtonType Type, QRect ButtonRect, QPixmap *Pixmap, CGame *Game, qreal ZOrder, qreal Angle)
{
    label = "Button";
    type = Type;
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

void CButtonDepr::onMousePressed(QMouseEvent *event)
{
    QPoint click = game->scene->toLocalPoint(event->localPos()).toPoint();
    qDebug() << click << " is in " << buttonRect
             << buttonRect.contains(click);
    bool visible = isVisible();
    if (buttonRect.contains(click)
                            && visible && event->button() == Qt::LeftButton)
    {
        qDebug() << "One Of Buttons Pressed";
        event->accept();
        game->pressedButton = type;
        emit pressed(type);
    }
}
