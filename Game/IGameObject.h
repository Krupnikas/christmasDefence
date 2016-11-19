#pragma once

#include <Game/Resource.h>

class CGame;

class IGameObject : public QObject
{
    Q_OBJECT
    
public:
    IGameObject();
    virtual ~IGameObject();
    void scaleItem(qreal scaleFactor);

    QPointF getCenter() const;
    void setCenter(const QPointF &value);
    
protected:

    qreal angle;
    int zOrder;
    
    QPointF center;
    QPointF leftTop;
    QSizeF size;
    
    QPixmap *pixmap;
    CGame *game;
    std::shared_ptr<QGraphicsItem> position;
    
};
