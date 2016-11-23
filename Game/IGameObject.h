#pragma once

#include <Game/Resource.h>

class CGame;

class IGameObject : public QObject
{
    Q_OBJECT
    
public:
    IGameObject();
    IGameObject(qreal angle, qreal zOrder, QPointF center, QPointF leftTop, QSizeF size, QPixmap *pixmap, CGame *game);
    std::shared_ptr<QGraphicsItem> position;
    virtual ~IGameObject();
    
    void scaleItem();
    void draw();
    void remove();
    
    void hide();
    void show();
    bool isVisible();
    
    QPointF getCenter() const;
    void setCenter(const QPointF &value);
    
    qreal getAngle() const;
    void setAngle(const qreal &value);
    
protected:
    
    qreal angle;
    qreal zOrder;
    
    QPointF center;
    QPointF leftTop;
    QSizeF size;
    
    QPixmap *pixmap;
    CGame *game;
    std::shared_ptr<QGraphicsItem> position;

};
