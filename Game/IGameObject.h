#pragma once

#include <Game/Resource.h>

class CGame;

class IGameObject : public QObject
{
    Q_OBJECT
    
public:
    IGameObject();
    IGameObject(qreal angle, qreal zOrder, QPointF center, QPointF leftTop, QSizeF textureSize, QPixmap *pixmap, CGame *game);
    virtual ~IGameObject();
    
    void scaleItem();
    void remove();
    
    virtual void draw();
    virtual void hide();
    virtual void show();
    bool isVisible();
    
    QPointF getCenter() const;
    void setCenter(const QPointF &value);
    
    qreal getAngle() const;
    void setAngle(const qreal &value);
    
    std::shared_ptr<QGraphicsItem> getPosition() const;
    
    qreal getZOrder() const;
    void setZOrder(const qreal &value);
    
    QSizeF getTextureSize() const;
    void setTextureSize(const QSizeF &value);
    
    QSizeF getSize() const;
    void setSize(const QSizeF &value);
    
    QPointF getLeftTop() const;
    void setLeftTop(const QPointF &value);
    
    QPixmap *getPixmap() const;
    
    CGame *getGame() const;
    
protected:
    
    qreal angle;
    qreal zOrder;
    
    QPointF center;
    QPointF leftTop;
    QSizeF textureSize;
    QSizeF size;
    
    QPixmap *pixmap;
    CGame *game;
    std::shared_ptr<QGraphicsItem> position;

};
