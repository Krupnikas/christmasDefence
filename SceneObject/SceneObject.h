#pragma once

#include <Resource.h>

class CGame;

class CSceneObject : public QObject
{
    Q_OBJECT
    
public:
    CSceneObject();
    CSceneObject(qreal angle, qreal zOrder, QPointF leftTop, QSizeF textureSize, std::shared_ptr<QPixmap> pixmap, CGame *game);
    virtual ~CSceneObject();
    
    virtual void scale();
    virtual void scaleWithLoss(QSizeF newSize);
    virtual void remove();
    virtual void draw();
    virtual void hide();
    virtual void show();
    virtual bool isVisible();
    
    virtual QPointF getCenter() const;
    virtual void setCenter(const QPointF &value);
    
    virtual qreal getAngle() const;
    virtual void setAngle(const qreal &value);
    
    virtual std::shared_ptr<QGraphicsItem> getPosition() const;
    
    virtual qreal getZOrder() const;
    virtual void setZOrder(const qreal &value);
    
    virtual QSizeF getTextureSize() const;
    virtual void setTextureSize(const QSizeF &value);
    
    virtual QSizeF getSize() const;
    virtual void setSize(const QSizeF &value);
    
    virtual QPointF getLeftTop() const;
    virtual void setLeftTop(const QPointF &value);
    
    virtual std::shared_ptr<QPixmap> getPixmap() const;
    virtual void setPixmap(std::shared_ptr<QPixmap> pixmap);
    
    CGame *getGame() const;
    
protected:
    
    QString label = "";

    qreal angle;
    qreal zOrder;
    
    QPointF center;
    QPointF leftTop;
    QSizeF textureSize;
    QSizeF size;
    
    std::shared_ptr<QPixmap> pixmap;
    CGame *game;
    std::shared_ptr<QGraphicsItem> position;

};
