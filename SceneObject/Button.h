#pragma once

#include <SceneObject/SceneObject.h>
#include <Game/Game.h>

class CButton: public CSceneObject
{
    Q_OBJECT
    
public:
    CButton(qreal zOrder, QPointF center, QSizeF size,
            QPixmap *normalPixmap, QPixmap *focusedPixmap, QPixmap *pressedPixmap,
            CGame *game, eButtonType type);
    
    virtual void scale();
    virtual void scaleWithLoss(QSizeF newSize);
    virtual void remove();
    virtual void draw();
    virtual void hide();
    virtual void show();
    virtual bool isVisible();
    
    virtual void setCenter(const QPointF &value);
    virtual void setAngle(const qreal &value);
    virtual void setZOrder(const qreal &value);
    virtual void setTextureSize(const QSizeF &value);
    virtual void setSize(const QSizeF &value);
    virtual void setLeftTop(const QPointF &value);
    
public slots:
    void onMouseMove(QMouseEvent *event);
    void onMouseDown(QMouseEvent *event);
    void onMouseUp(QMouseEvent *event);
    
signals:
    void pressed(eButtonType Type);
    
//private methods
private:
    checkInside(QPointF p);
    
//private fields
private:
    std::shared_ptr<CSceneObject> normalItem;
    std::shared_ptr<CSceneObject> focusedItem;
    std::shared_ptr<CSceneObject> pressedItem;
    
    eButtonType type;
    
    bool mouseDown;
};
